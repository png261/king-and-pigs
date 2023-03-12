#include "ContactListener.hpp"
#include <iostream>
#include "ItemObject.hpp"
#include "Pig.hpp"

void ContactListener::BeginContact(b2Contact* contact)
{
    ItemContact(contact);

    JumpBeginContact(contact);
    EnemyVisionBeginContact(contact);
    EnemyAttackRangePlayerBeginContact(contact);
}

void ContactListener::EndContact(b2Contact* contact)
{
    JumpEndContact(contact);
    EnemyVisionEndContact(contact);
    EnemyAttackRangePlayerEndContact(contact);
}

void ContactListener::EnemyAttackRangePlayerBeginContact(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;
    bool isTrue = (catA | catB) == (Box2D::CAT_PLAYER | Box2D::CAT_ATTACK_SENSOR);
    return;

    if (!isTrue) {
        return;
    }

    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(A->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(true);
        }
    }

    if (catB == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(B->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(true);
        }
    }
};

void ContactListener::EnemyAttackRangePlayerEndContact(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;
    bool isTrue = (catA | catB) == (Box2D::CAT_PLAYER | Box2D::CAT_ATTACK_SENSOR);
    if (!isTrue) {
        return;
    }
    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(A->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(false);
        }
    }

    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(B->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(false);
        }
    }
};

void ContactListener::EnemyVisionBeginContact(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;
    bool isSeeing = (catA | catB) == (Box2D::CAT_PLAYER | Box2D::CAT_ENEMY_VISION_SENSOR);
    if (!isSeeing) {
        return;
    }
    Pig* enemy = nullptr;
    if (catA == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(A->GetBody()->GetUserData().pointer));
    }

    if (catB == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(B->GetBody()->GetUserData().pointer));
    }
    enemy->setSeeingPlayer(true);
}

void ContactListener::EnemyVisionEndContact(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;
    bool isSeeing = (catA | catB) == (Box2D::CAT_PLAYER | Box2D::CAT_ENEMY_VISION_SENSOR);
    if (!isSeeing) {
        return;
    }
    Pig* enemy = nullptr;
    if (catA == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(A->GetBody()->GetUserData().pointer));
    }

    if (catB == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(B->GetBody()->GetUserData().pointer));
    }
    enemy->setSeeingPlayer(false);
}

void ContactListener::ItemContact(b2Contact* contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    uint16 const catB = fixtureB->GetFilterData().categoryBits;
    uint16 const catA = fixtureA->GetFilterData().categoryBits;
    if ((catA | catB) != (Box2D::CAT_ITEM | Box2D::CAT_PLAYER)) {
        return;
    }

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
    if (!((catA | catB) & Box2D::CAT_FOOT_SENSOR)) {
        return;
    }

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
    if (!((catA | catB) & Box2D::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* objA = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* objB = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == Box2D::CAT_FOOT_SENSOR) {
        objA->changeFootContact(-1);
    } else if (catB == Box2D::CAT_FOOT_SENSOR) {
        objB->changeFootContact(-1);
    }
}
