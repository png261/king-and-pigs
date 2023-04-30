#include "VisionObject.hpp"

#include "DebugDraw.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "GameStateMachine.hpp"
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
        b2Vec2 start = Utils::pixelToMeter(raycast.start);
        b2Vec2 end = Utils::pixelToMeter(raycast.end);

        VisionRayCastCallback callback;
        PhysicWorld::Instance().getWorld()->RayCast(&callback, start, end);
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
        b2Vec2 start = Utils::pixelToMeter(raycast.start);
        b2Vec2 end = Utils::pixelToMeter(raycast.end);
        debug.DrawSegment(start, end, {1, 1, 1, 1});
    }
}

bool VisionObject::isSeeing(ContactCategory category) const
{
    return seeing_category_ & category;
}
