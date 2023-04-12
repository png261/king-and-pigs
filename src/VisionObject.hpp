#pragma once
#include <iostream>
#include <vector>
#include "PhysicWorld.hpp"

class VisionRayCastCallback : public b2RayCastCallback
{
public:
    VisionRayCastCallback()
        : m_fraction(1)
    {}

    float ReportFixture(b2Fixture* fixture, const b2Vec2&, const b2Vec2&, float fraction)
    {
        if (fixture->IsSensor()) {
            return 1;
        }

        m_seeingCategory =
            static_cast<PhysicWorld::Category>(fixture->GetFilterData().categoryBits);
        m_fraction = fraction;

        return fraction;
    }

    PhysicWorld::Category m_seeingCategory;
    float m_fraction;
};

struct raycast
{
    b2Vec2 start;
    b2Vec2 end;
};

class VisionObject
{
public:
    VisionObject(float range);
    virtual void update();
    virtual void debugDraw();

protected:
    uint16 m_seeingCategory;
    float m_visionFraction;
    int m_visionRange;
    float m_visionNearestDistance;
    std::vector<raycast> m_raycast;
};
