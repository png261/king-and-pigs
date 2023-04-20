#pragma once
#include <iostream>
#include <vector>
#include "PhysicWorld.hpp"

class VisionRayCastCallback : public b2RayCastCallback
{
public:
    VisionRayCastCallback()
        : fraction_(1)
    {}

    float ReportFixture(b2Fixture* fixture, const b2Vec2&, const b2Vec2&, float fraction)
    {
        if (fixture->IsSensor()) {
            return 1;
        }

        seeing_category_ =
            static_cast<PhysicWorld::Category>(fixture->GetFilterData().categoryBits);
        fraction_ = fraction;

        return fraction;
    }

    PhysicWorld::Category seeing_category_;
    float fraction_;
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
    bool isSeeing(PhysicWorld::Category category);

protected:
    uint16 seeing_category_;
    float fraction_;
    int vision_range_;
    float vision_nearest_distance_;
    std::vector<raycast> raycast_;
};
