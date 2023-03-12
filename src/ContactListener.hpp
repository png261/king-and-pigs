#pragma once

#include "Box2D.hpp"

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
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
    void JumpBeginContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
    void JumpEndContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
    void EnemyVisionBeginContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
    void EnemyVisionEndContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
    void EnemyAttackRangePlayerBeginContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
    void EnemyAttackRangePlayerEndContact(
        b2Fixture* const fixtureA,
        b2Fixture* const fixtureB,
        Box2D::FilterCategory const catA,
        Box2D::FilterCategory const catB);
};
