#include "ContactListener.hpp"

#include "AttackerObject.hpp"
#include "DoorIn.hpp"
#include "DoorOut.hpp"
#include "Game.hpp"
#include "ItemObject.hpp"
#include "Log.hpp"
#include "PhysicManager.hpp"
#include "PhysicObject.hpp"
#include "Pig.hpp"

void ContactListener::realTimeListener(b2Contact* const contactList)
{
    for (b2Contact* contact = contactList; contact != nullptr; contact = contact->GetNext()) {
        AttackListener(contact);
        EnterDoorListener(contact);
    }
}

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
    auto const categoryA = static_cast<ContactCategory>(fixtureA->GetFilterData().categoryBits);

    if (categoryA == ContactCategory::CAT_ONE_WAY_WALL) {
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
    auto const categoryA = static_cast<ContactCategory>(fixtureA->GetFilterData().categoryBits);
    auto const categoryB = static_cast<ContactCategory>(fixtureB->GetFilterData().categoryBits);

    if ((categoryA | categoryB) != (ContactCategory::CAT_ITEM | ContactCategory::CAT_PLAYER)) {
        return;
    }

    ItemObject* bonusItem = nullptr;
    if (categoryA == ContactCategory::CAT_ITEM) {
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
    auto const categoryA = static_cast<ContactCategory>(fixtureA->GetFilterData().categoryBits);
    auto const categoryB = static_cast<ContactCategory>(fixtureB->GetFilterData().categoryBits);
    if (!((categoryA | categoryB) & ContactCategory::CAT_FOOT_SENSOR)) {
        return;
    }

    auto* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    auto* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (categoryA == ContactCategory::CAT_FOOT_SENSOR) {
        A->changeFootContact(+1);
    } else if (categoryB == ContactCategory::CAT_FOOT_SENSOR) {
        B->changeFootContact(+1);
    }
}

void ContactListener::FootEndContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    auto const categoryA = static_cast<ContactCategory>(fixtureA->GetFilterData().categoryBits);
    auto const categoryB = static_cast<ContactCategory>(fixtureB->GetFilterData().categoryBits);
    if (!((categoryA | categoryB) & ContactCategory::CAT_FOOT_SENSOR)) {
        return;
    }

    auto* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    auto* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (categoryA == ContactCategory::CAT_FOOT_SENSOR) {
        A->changeFootContact(-1);
    } else if (categoryB == ContactCategory::CAT_FOOT_SENSOR) {
        B->changeFootContact(-1);
    }
}

void ContactListener::EnterDoorListener(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    const uint16 catA = fixtureA->GetFilterData().categoryBits;
    const uint16 catB = fixtureB->GetFilterData().categoryBits;

    if ((catA | catB) != (ContactCategory::CAT_DOOR_IN | ContactCategory::CAT_PLAYER)) {
        return;
    }

    DoorIn* door = nullptr;
    Player* player = nullptr;

    if (catA == ContactCategory::CAT_DOOR_IN) {
        door = (DoorIn*)(fixtureA->GetBody()->GetUserData().pointer);
        player = (Player*)(fixtureB->GetBody()->GetUserData().pointer);
    } else {
        door = (DoorIn*)(fixtureB->GetBody()->GetUserData().pointer);
        player = (Player*)(fixtureA->GetBody()->GetUserData().pointer);
    }

    if (player == nullptr || door == nullptr) {
        return;
    }

    if (!player->isWantEnterDoor()) {
        return;
    }

    if (door->isOpened()) {
        Game::Instance().nextLevel();
        return;
    }

    player->enterDoor();
    door->open();
}

void ContactListener::AttackListener(b2Contact* const contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;

    if (catB == ContactCategory::CAT_ATTACK_SENSOR &&
        catA &
            (ContactCategory::CAT_PIG | ContactCategory::CAT_PLAYER | ContactCategory::CAT_BOX)) {
        handleAttack(B, A);
    }
}

void ContactListener::handleAttack(b2Fixture* const Attacker, b2Fixture* const Defender)
{
    AttackerObject* const A =
        dynamic_cast<AttackerObject*>((GameObject*)(Attacker->GetBody()->GetUserData().pointer));
    DamageableObject* const B =
        dynamic_cast<DamageableObject*>((GameObject*)(Defender->GetBody()->GetUserData().pointer));

    if (A == nullptr || B == nullptr || !A->isDaming()) {
        return;
    }

    B->damage(A->getDamage());
}
