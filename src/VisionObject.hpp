#pragma once

#include <vector>

#include "PhysicManager.hpp"

class VisionRayCastCallback final : public b2RayCastCallback
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

        seeing_category_ = static_cast<ContactCategory>(fixture->GetFilterData().categoryBits);
        fraction_ = fraction;

        return fraction;
    }

    ContactCategory seeing_category_;
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
    VisionObject(const float range);
    virtual void update();
    virtual void debugDraw() const;
    virtual bool isSeeing(const ContactCategory category) const;

protected:
    uint16 seeing_category_;
    float fraction_;
    int vision_range_;
    float vision_nearest_distance_;
    std::vector<raycast> raycast_;
};
