#include "ContactListener.hpp"
#include "ItemObject.hpp"
#include "Pig.hpp"

void ContactListener::BeginContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    Box2D::FilterCategory const catA =
        static_cast<Box2D::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    Box2D::FilterCategory const catB =
        static_cast<Box2D::FilterCategory>(fixtureB->GetFilterData().categoryBits);

    ItemContact(fixtureA, fixtureB, catA, catB);
    JumpBeginContact(fixtureA, fixtureB, catA, catB);
    EnemyVisionBeginContact(fixtureA, fixtureB, catA, catB);
    EnemyAttackRangePlayerBeginContact(fixtureA, fixtureB, catA, catB);
}

void ContactListener::EndContact(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    Box2D::FilterCategory const catA =
        static_cast<Box2D::FilterCategory>(fixtureA->GetFilterData().categoryBits);
    Box2D::FilterCategory const catB =
        static_cast<Box2D::FilterCategory>(fixtureB->GetFilterData().categoryBits);

    JumpEndContact(fixtureA, fixtureB, catA, catB);
    EnemyVisionEndContact(fixtureA, fixtureB, catA, catB);
    EnemyAttackRangePlayerEndContact(fixtureA, fixtureB, catA, catB);
}

void ContactListener::PreSolve(b2Contact* const contact, const b2Manifold* oldManifold) {}

void ContactListener::PostSolve(b2Contact* const contact, const b2ContactImpulse* impulse){};

void ContactListener::EnemyAttackRangePlayerBeginContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    return;

    if ((catA | catB) != (Box2D::CAT_PLAYER | Box2D::CAT_ATTACK_SENSOR)) {
        return;
    }

    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(true);
        }
    }

    if (catB == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(true);
        }
    }
};

void ContactListener::EnemyAttackRangePlayerEndContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    if ((catA | catB) != (Box2D::CAT_PLAYER | Box2D::CAT_ATTACK_SENSOR)) {
        return;
    }

    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(false);
        }
    }

    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        Pig* enemy = dynamic_cast<Pig*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
        if (enemy != nullptr) {
            enemy->setCanAttackPlayer(false);
        }
    }
};

void ContactListener::EnemyVisionBeginContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    if ((catA | catB) != (Box2D::CAT_PLAYER | Box2D::CAT_ENEMY_VISION_SENSOR)) {
        return;
    }

    Pig* enemy = nullptr;
    if (catA == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
    }

    if (catB == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
    }
    enemy->setSeeingPlayer(true);
}

void ContactListener::EnemyVisionEndContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    if ((catA | catB) != (Box2D::CAT_PLAYER | Box2D::CAT_ENEMY_VISION_SENSOR)) {
        return;
    }

    Pig* enemy = nullptr;
    if (catA == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
    }

    if (catB == Box2D::CAT_ENEMY_VISION_SENSOR) {
        enemy = dynamic_cast<Pig*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
    }
    enemy->setSeeingPlayer(false);
}

void ContactListener::ItemContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    if ((catA | catB) != (Box2D::CAT_ITEM | Box2D::CAT_PLAYER)) {
        return;
    }

    if (catA == Box2D::CAT_ITEM) {
        ((ItemObject*)(fixtureA->GetBody()->GetUserData().pointer))->bonus();
    } else {
        ((ItemObject*)(fixtureB->GetBody()->GetUserData().pointer))->bonus();
    }
}

void ContactListener::JumpBeginContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    if (!((catA | catB) & Box2D::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* const A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* const B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == Box2D::CAT_FOOT_SENSOR) {
        A->changeFootContact(+1);
    } else if (catB == Box2D::CAT_FOOT_SENSOR) {
        B->changeFootContact(+1);
    }
}

void ContactListener::JumpEndContact(
    b2Fixture* const fixtureA,
    b2Fixture* const fixtureB,
    Box2D::FilterCategory const catA,
    Box2D::FilterCategory const catB)
{
    if (!((catA | catB) & Box2D::CAT_FOOT_SENSOR)) {
        return;
    }

    GameObject* A = (GameObject*)(fixtureA->GetBody()->GetUserData().pointer);
    GameObject* B = (GameObject*)(fixtureB->GetBody()->GetUserData().pointer);

    if (catA == Box2D::CAT_FOOT_SENSOR) {
        A->changeFootContact(-1);
    } else if (catB == Box2D::CAT_FOOT_SENSOR) {
        B->changeFootContact(-1);
    }
}
