#pragma once

#include "Box2D.hpp"

class ContactListener final : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

private:
    void ItemContact(b2Contact* contact);

    void JumpBeginContact(b2Contact* contact);
    void JumpEndContact(b2Contact* contact);

    void EnemyVisionBeginContact(b2Contact* contact);
    void EnemyVisionEndContact(b2Contact* contact);
    void EnemyAttackRangePlayerBeginContact(b2Contact* contact);
    void EnemyAttackRangePlayerEndContact(b2Contact* contact);
};
