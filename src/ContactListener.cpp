#include "ContactListener.hpp"
#include "ItemObject.hpp"
#include "Pig.hpp"

void ContactListener::BeginContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::FilterCategory const catA =
        static_cast<PhysicWorld::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::FilterCategory const catB =
        static_cast<PhysicWorld::FilterCategory>(fixtureB->GetFilterData().categoryBits);

    ItemContact(fixtureA, fixtureB, catA, catB);
    JumpBeginContact(fixtureA, fixtureB, catA, catB);
}

void ContactListener::EndContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    PhysicWorld::FilterCategory const catA =
        static_cast<PhysicWorld::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    PhysicWorld::FilterCategory const catB =
        static_cast<PhysicWorld::FilterCategory>(fixtureB->GetFilterData().categoryBits);

    JumpEndContact(fixtureA, fixtureB, catA, catB);
}

void ContactListener::PreSolve(b2Contact* const contact, const b2Manifold* oldManifold) {}

void ContactListener::PostSolve(b2Contact* const contact, const b2ContactImpulse* impulse){};

void ContactListener::ItemContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    PhysicWorld::FilterCategory const catA,
    PhysicWorld::FilterCategory const catB)
{
    if (catA != PhysicWorld::CAT_ITEM || catB != PhysicWorld::CAT_PLAYER) {
        return;
    }

    ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer))->bonus();
}

void ContactListener::JumpBeginContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    PhysicWorld::FilterCategory const catA,
    PhysicWorld::FilterCategory const catB)
{
    if (!((catA | catB) & PhysicWorld::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == PhysicWorld::CAT_FOOT_SENSOR) {
        A->changeFootContact(+1);
    } else if (catB == PhysicWorld::CAT_FOOT_SENSOR) {
        B->changeFootContact(+1);
    }
}

void ContactListener::JumpEndContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    PhysicWorld::FilterCategory const catA,
    PhysicWorld::FilterCategory const catB)
{
    if (!((catA | catB) & PhysicWorld::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == PhysicWorld::CAT_FOOT_SENSOR) {
        A->changeFootContact(-1);
    } else if (catB == PhysicWorld::CAT_FOOT_SENSOR) {
        B->changeFootContact(-1);
    }
}
