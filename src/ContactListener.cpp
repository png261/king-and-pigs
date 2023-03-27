#include "ContactListener.hpp"
#include <iostream>
#include "ItemObject.hpp"
#include "Log.hpp"
#include "PhysicObject.hpp"
#include "Pig.hpp"

void ContactListener::BeginContact(b2Contact* const contact)
{
    ItemBeginContact(contact);
    FootBeginContact(contact);
}

void ContactListener::EndContact(b2Contact* const contact)
{
    FootEndContact(contact);
}

void ContactListener::PreSolve(b2Contact* const contact, const b2Manifold* oldManifold)
{
    OneWayPreSolve(contact, oldManifold);
}

void ContactListener::PostSolve(b2Contact* const contact, const b2ContactImpulse* impulse){

};

void ContactListener::OneWayPreSolve(b2Contact* const contact, const b2Manifold* oldManifold)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::Category const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::Category const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);

    if (categoryA == PhysicWorld::CAT_ONE_WAY_WALL) {
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);
        if (worldManifold.normal.y < 0 && fixtureB->GetBody()->GetLinearVelocity().y >= 0) {
            contact->SetEnabled(true);
        } else {
            contact->SetEnabled(false);
        }
        return;
    }
};

void ContactListener::ItemBeginContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::Category const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::Category const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);
    if (categoryA != PhysicWorld::CAT_ITEM || categoryB != PhysicWorld::CAT_PLAYER) {
        return;
    }

    ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer))->bonus();
}

void ContactListener::FootBeginContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::Category const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::Category const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);

    if (categoryB != PhysicWorld::CAT_FOOT_SENSOR) {
        return;
    }

    GameObject* const Obj = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);
    Obj->changeFootContact(+1);
}

void ContactListener::FootEndContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::Category const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::Category const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);

    if (categoryB != PhysicWorld::CAT_FOOT_SENSOR) {
        return;
    }

    GameObject* const Obj = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);
    Obj->changeFootContact(-1);
}
