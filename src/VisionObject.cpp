#include "VisionObject.hpp"
#include "DebugDraw.hpp"
#include "Game.hpp"

VisionObject::VisionObject(int range)
    : m_start(0, 0)
    , m_end(0, 0)
    , m_fraction(1)
    , m_orignRange(range)
    , m_nearestDistance(range)
{}

void VisionObject::update(b2Vec2 start, b2Vec2 end)
{
    m_start = PhysicWorld::pixelToMeter(start);
    m_end = PhysicWorld::pixelToMeter(end);
    VisionRayCastCallback callback;
    PhysicWorld::Instance()->getWorld()->RayCast(&callback, m_start, m_end);
    m_seeingCategory = callback.m_seeingCategory;
    m_fraction = callback.m_fraction;
    m_nearestDistance = m_orignRange * m_fraction;
}

void VisionObject::debugDraw()
{
    if (Game::Instance()->isDebug() == false) {
        return;
    }
    DebugDraw* debug = new DebugDraw(Game::Instance()->getWindow());
    debug->DrawSegment(m_start, m_end, {1, 1, 1, 1});
}
