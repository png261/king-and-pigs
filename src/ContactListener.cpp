#include "ContactListener.hpp"
#include <iostream>
#include "ItemObject.hpp"
#include "Log.hpp"
#include "PhysicObject.hpp"
#include "PhysicWorld.hpp"
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

void ContactListener::PostSolve(b2Contact* const, const b2ContactImpulse*){};

void ContactListener::OneWayPreSolve(b2Contact* const contact, const b2Manifold* oldManifold)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    auto const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);

    if (categoryA == PhysicWorld::CAT_ONE_WAY_WALL) {
        if (oldManifold->localNormal.y < 0 && fixtureB->GetBody()->GetLinearVelocity().y >= 0) {
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
    auto const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    auto const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);

    if ((categoryA | categoryB) != (PhysicWorld::CAT_ITEM | PhysicWorld::CAT_PLAYER)) {
        return;
    }

    ItemObject* bonusItem = nullptr;
    if (categoryA == PhysicWorld::CAT_ITEM) {
        bonusItem = ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer));
    } else {
        bonusItem = ((ItemObject*)(fixtureB->GetBody()->GetUserData().pointer));
    }

    if (bonusItem == nullptr) {
        return;
    }

    bonusItem->bonus();
}

void ContactListener::FootBeginContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    auto const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    auto const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);
    if (!((categoryA | categoryB) & PhysicWorld::CAT_FOOT_SENSOR)) {
        return;
    }

    auto* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    auto* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (categoryA == PhysicWorld::CAT_FOOT_SENSOR) {
        A->changeFootContact(+1);
    } else if (categoryB == PhysicWorld::CAT_FOOT_SENSOR) {
        B->changeFootContact(+1);
    }
}

void ContactListener::FootEndContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    auto const categoryA =
        static_cast<PhysicWorld::Category>(fixtureA->GetFilterData().categoryBits);
    auto const categoryB =
        static_cast<PhysicWorld::Category>(fixtureB->GetFilterData().categoryBits);
    if (!((categoryA | categoryB) & PhysicWorld::CAT_FOOT_SENSOR)) {
        return;
    }

    auto* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    auto* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (categoryA == PhysicWorld::CAT_FOOT_SENSOR) {
        A->changeFootContact(-1);
    } else if (categoryB == PhysicWorld::CAT_FOOT_SENSOR) {
        B->changeFootContact(-1);
    }
}
