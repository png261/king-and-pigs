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

    if (catA == Box2D::ITEM && catB == Box2D::PLAYER) {
        reinterpret_cast<ItemObject*>(fixtureA->GetBody()->GetUserData().pointer)->bonus();
    }

    if (catA == Box2D::PLAYER && catB == Box2D::ITEM) {
        reinterpret_cast<ItemObject*>(fixtureB->GetBody()->GetUserData().pointer)->bonus();
    }
}

void ContactListener::JumpBeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catA = fixtureA->GetFilterData().categoryBits;
    uint16 catB = fixtureB->GetFilterData().categoryBits;

    if (catA == Box2D::PLAYER_FOOT) {
        reinterpret_cast<PlatformerObject*>(fixtureA->GetBody()->GetUserData().pointer)
            ->changeFootContact(+1);
    } else {
        reinterpret_cast<PlatformerObject*>(fixtureB->GetBody()->GetUserData().pointer)
            ->changeFootContact(+1);
    }
}

void ContactListener::JumpEndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catA = fixtureA->GetFilterData().categoryBits;
    uint16 catB = fixtureB->GetFilterData().categoryBits;

    if (catA == Box2D::PLAYER_FOOT) {
        reinterpret_cast<PlatformerObject*>(fixtureA->GetBody()->GetUserData().pointer)
            ->changeFootContact(-1);
    } else {
        reinterpret_cast<PlatformerObject*>(fixtureB->GetBody()->GetUserData().pointer)
            ->changeFootContact(-1);
    }
}

void ContactListener::BeginContact(b2Contact* contact)
{
    uint16 catA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 catB = contact->GetFixtureB()->GetFilterData().categoryBits;

    if (catA == Box2D::ITEM || catB == Box2D::ITEM) {
        ItemContact(contact);
    }

    if (catA == Box2D::PLAYER_FOOT || catB == Box2D::PLAYER_FOOT) {
        JumpBeginContact(contact);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    uint16 catA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 catB = contact->GetFixtureB()->GetFilterData().categoryBits;

    if (catA == Box2D::PLAYER_FOOT || catB == Box2D::PLAYER_FOOT) {
        JumpEndContact(contact);
    }
}
