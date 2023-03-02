#include "ContactListener.hpp"
#include <iostream>
#include "ItemObject.hpp"
#include "GameObject.hpp"

void ContactListener::ItemContact(b2Contact* contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    uint16 const catB = fixtureB->GetFilterData().categoryBits;
    uint16 const catA = fixtureA->GetFilterData().categoryBits;

    if (catA == Box2D::CAT_ITEM) {
        ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer))->bonus();
    } else {
        ((ItemObject*)(fixtureB->GetBody()->GetUserData().pointer))->bonus();
    }
}

void ContactListener::JumpBeginContact(b2Contact* contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    uint16 const catA = fixtureA->GetFilterData().categoryBits;
    uint16 const catB = fixtureB->GetFilterData().categoryBits;
    GameObject* const objA = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* const objB = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == Box2D::CAT_FOOT_SENSOR) {
        objA->changeFootContact(+1);
    } else if (catB == Box2D::CAT_FOOT_SENSOR) {
        objB->changeFootContact(+1);
    }
}

void ContactListener::JumpEndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catA = fixtureA->GetFilterData().categoryBits;
    uint16 catB = fixtureB->GetFilterData().categoryBits;
    GameObject* objA = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* objB = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == Box2D::CAT_FOOT_SENSOR) {
        objA->changeFootContact(-1);
    } else if (catB == Box2D::CAT_FOOT_SENSOR) {
        objB->changeFootContact(-1);
    }
}

void ContactListener::BeginContact(b2Contact* contact)
{
    uint16 const catA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 const catB = contact->GetFixtureB()->GetFilterData().categoryBits;

    if ((catA | catB) == (Box2D::CAT_ITEM | Box2D::CAT_PLAYER)) {
        ItemContact(contact);
    }

    if ((catA | catB) & Box2D::CAT_FOOT_SENSOR) {
        JumpBeginContact(contact);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    uint16 const catA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 const catB = contact->GetFixtureB()->GetFilterData().categoryBits;

    if ((catA | catB) & Box2D::CAT_FOOT_SENSOR) {
        JumpEndContact(contact);
    }
}
