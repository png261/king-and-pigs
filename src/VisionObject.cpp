#include "VisionObject.hpp"
#include <iostream>
#include "DebugDraw.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "GameStateMachine.hpp"

VisionObject::VisionObject(float range)
    : m_visionFraction(1)
    , m_visionRange(range)
    , m_visionNearestDistance(range)
{}

void VisionObject::update()
{
    m_seeingCategory = 0;
    m_visionNearestDistance = m_visionRange;
    for (auto& raycast : m_raycast) {
        b2Vec2 start = PhysicWorld::pixelToMeter(raycast.start);
        b2Vec2 end = PhysicWorld::pixelToMeter(raycast.end);

        VisionRayCastCallback callback;
        PhysicWorld::Instance().getWorld()->RayCast(&callback, start, end);
        m_seeingCategory = m_seeingCategory | callback.m_seeingCategory;

        m_visionNearestDistance = callback.m_fraction * m_visionRange < m_visionNearestDistance
                                      ? callback.m_fraction * m_visionRange
                                      : m_visionNearestDistance;
    }
}

void VisionObject::debugDraw()
{
    if (Game::Instance().isDebug() == false) {
        return;
    }

    DebugDraw debug(Game::Instance().getWindow());
    for (auto& raycast : m_raycast) {
        b2Vec2 start = PhysicWorld::pixelToMeter(raycast.start);
        b2Vec2 end = PhysicWorld::pixelToMeter(raycast.end);
        debug.DrawSegment(start, end, {1, 1, 1, 1});
    }
}
