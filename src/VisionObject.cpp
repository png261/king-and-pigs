#include "VisionObject.hpp"

#include "DebugDraw.hpp"
#include "Game.hpp"
#include "Utils.hpp"

VisionObject::VisionObject(float range)
    : fraction_(1)
    , vision_range_(range)
    , vision_nearest_distance_(range)
{}

void VisionObject::update()
{
    seeing_category_ = 0;
    vision_nearest_distance_ = vision_range_;

    for (auto& raycast : raycast_) {
        VisionRayCastCallback callback;
        PhysicManager::Instance().getWorld()->RayCast(
            &callback,
            Utils::pixelToMeter(raycast.start),
            Utils::pixelToMeter(raycast.end));

        seeing_category_ = seeing_category_ | callback.seeing_category_;

        vision_nearest_distance_ = callback.fraction_ * vision_range_ < vision_nearest_distance_
                                       ? callback.fraction_ * vision_range_
                                       : vision_nearest_distance_;
    }
}

void VisionObject::debugDraw() const
{
    if (!Game::Instance().isDebug()) {
        return;
    }

    DebugDraw debug(Game::Instance().getWindow());
    for (auto& raycast : raycast_) {
        debug.DrawSegment(
            Utils::pixelToMeter(raycast.start),
            Utils::pixelToMeter(raycast.end),
            {1, 1, 1, 1});
    }
}

bool VisionObject::isSeeing(const ContactCategory category) const
{
    return seeing_category_ & category;
}
