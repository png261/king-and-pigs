#pragma once
#include <iostream>
#include "PhysicWorld.hpp"

class VisionRayCastCallback : public b2RayCastCallback
{
public:
    VisionRayCastCallback()
        : m_fraction(1)
    {}

    float
    ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
    {
        if (fixture->IsSensor()) {
            return 1;
        }

        m_seeingCategory =
            static_cast<PhysicWorld::FilterCategory>(fixture->GetFilterData().categoryBits);
        m_fraction = fraction;

        return fraction;
    }

    PhysicWorld::FilterCategory m_seeingCategory;
    float m_fraction;
};

class VisionObject
{
public:
    VisionObject(int range);
    virtual void update(b2Vec2 start, b2Vec2 end);
    virtual void debugDraw();

protected:
    PhysicWorld::FilterCategory m_seeingCategory;
    float m_fraction;
    int m_orignRange;
    int m_nearestDistance;

private:
    b2Vec2 m_start;
    b2Vec2 m_end;
};
