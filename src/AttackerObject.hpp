#pragma once

#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "PhysicWorld.hpp"
#include "Stopwatch.hpp"

class AttackerObject
{
public:
    AttackerObject(const int damage, const int range, const int attackSpeed);

    virtual void update();
    virtual void attack();

    virtual bool canAttack() const;
    virtual int getDamage() const;
    virtual bool isAttack() const;

protected:
    Timer attackTimer;

    int m_attackDamage;
    int m_attackRange;
    int m_attackSpeed;

    bool m_bAttack;
    bool m_bCanAttack;
};
