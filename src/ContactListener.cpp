#include "ContactListener.hpp"
#include "ItemObject.hpp"
#include "Log.hpp"
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
    PhysicWorld::FilterCategory const categoryA =
        static_cast<PhysicWorld::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::FilterCategory const categoryB =
        static_cast<PhysicWorld::FilterCategory>(fixtureB->GetFilterData().categoryBits);

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
    PhysicWorld::FilterCategory const categoryA =
        static_cast<PhysicWorld::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::FilterCategory const categoryB =
        static_cast<PhysicWorld::FilterCategory>(fixtureB->GetFilterData().categoryBits);
    if (categoryA != PhysicWorld::CAT_ITEM || categoryB != PhysicWorld::CAT_PLAYER) {
        return;
    }

    ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer))->bonus();
}

void ContactListener::FootBeginContact(b2Contact* const contact)
{
    if (contact->IsEnabled() == false) {
        return;
    }

    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::FilterCategory const categoryA =
        static_cast<PhysicWorld::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::FilterCategory const categoryB =
        static_cast<PhysicWorld::FilterCategory>(fixtureB->GetFilterData().categoryBits);
    if (!((categoryA | categoryB) & PhysicWorld::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (categoryA == PhysicWorld::CAT_FOOT_SENSOR) {
        A->changeFootContact(+1);
    } else if (categoryB == PhysicWorld::CAT_FOOT_SENSOR) {
        B->changeFootContact(+1);
    }
}

void ContactListener::FootEndContact(b2Contact* const contact)
{
    if (contact->IsEnabled() == false) {
        return;
    }

    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::FilterCategory const categoryA =
        static_cast<PhysicWorld::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::FilterCategory const categoryB =
        static_cast<PhysicWorld::FilterCategory>(fixtureB->GetFilterData().categoryBits);
    if (!((categoryA | categoryB) & PhysicWorld::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (categoryA == PhysicWorld::CAT_FOOT_SENSOR) {
        A->changeFootContact(-1);
    } else if (categoryB == PhysicWorld::CAT_FOOT_SENSOR) {
        B->changeFootContact(-1);
    }
}
