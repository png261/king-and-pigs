#pragma once

#include "PhysicWorld.hpp"

class ContactListener final : public b2ContactListener
{
public:
    void BeginContact(b2Contact* const contact);
    void EndContact(b2Contact* const contact);
    void PreSolve(b2Contact* const contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* const contact, const b2ContactImpulse* impulse);

private:
    void ItemContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        PhysicWorld::FilterCategory const catA,
        PhysicWorld::FilterCategory const catB);
    void JumpBeginContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        PhysicWorld::FilterCategory const catA,
        PhysicWorld::FilterCategory const catB);
    void JumpEndContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        PhysicWorld::FilterCategory const catA,
        PhysicWorld::FilterCategory const catB);
};
