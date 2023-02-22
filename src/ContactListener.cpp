#include "ContactListener.hpp"
#include <iostream>
#include "ItemObject.hpp"
#include "PlatformerObject.hpp"

void ContactListener::ItemContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catB = fixtureB->GetFilterData().categoryBits;
    uint16 catA = fixtureA->GetFilterData().categoryBits;

    if (catA == Box2D::CAT_ITEM) {
        ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer))->bonus();
    } else {
        ((ItemObject*)(fixtureB->GetBody()->GetUserData().pointer))->bonus();
    }
}

void ContactListener::JumpBeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catA = fixtureA->GetFilterData().categoryBits;
    uint16 catB = fixtureB->GetFilterData().categoryBits;
    PlatformerObject* objA = (PlatformerObject*)(fixtureA->GetBody()->GetUserData().pointer);
    PlatformerObject* objB = (PlatformerObject*)(fixtureB->GetBody()->GetUserData().pointer);

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
    PlatformerObject* objA = (PlatformerObject*)(fixtureA->GetBody()->GetUserData().pointer);
    PlatformerObject* objB = (PlatformerObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == Box2D::CAT_FOOT_SENSOR) {
        objA->changeFootContact(-1);
    } else if (catB == Box2D::CAT_FOOT_SENSOR) {
        objB->changeFootContact(-1);
    }
}

void ContactListener::BeginContact(b2Contact* contact)
{
    uint16 catA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 catB = contact->GetFixtureB()->GetFilterData().categoryBits;

    if ((catA | catB) == (Box2D::CAT_ITEM | Box2D::CAT_PLAYER)) {
        ItemContact(contact);
    }

    if ((catA | catB) & Box2D::CAT_FOOT_SENSOR) {
        JumpBeginContact(contact);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    uint16 catA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 catB = contact->GetFixtureB()->GetFilterData().categoryBits;

    if ((catA | catB) & Box2D::CAT_FOOT_SENSOR) {
        JumpEndContact(contact);
    }
}
