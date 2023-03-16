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
    void ItemBeginContact(b2Contact* const contact);
    void FootBeginContact(b2Contact* const contact);

    void FootEndContact(b2Contact* const contact);

    void OneWayPreSolve(b2Contact* const contact, const b2Manifold* oldManifold);
};
