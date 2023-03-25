#pragma once
#include <iostream>
#include "PhysicWorld.hpp"

class rayCastCallback : public b2RayCastCallback
{
public:
    rayCastCallback()
        : m_fraction(1)
    {}

    float
    ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
    {
        m_hitCategory =
            static_cast<PhysicWorld::FilterCategory>(fixture->GetFilterData().categoryBits);
        m_fraction = fraction;
        std::cout << m_fraction << std::endl;

        return fraction;
    }

    PhysicWorld::FilterCategory m_hitCategory;
    float m_fraction;
};

class VisionObject
{
public:
    VisionObject();
    virtual void update(b2Vec2 start, b2Vec2 end);
    virtual void debugDraw();

protected:
    PhysicWorld::FilterCategory m_hitCategory;
    float m_fraction;
    b2Vec2 m_start;
    b2Vec2 m_end;
};
