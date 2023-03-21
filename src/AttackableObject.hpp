#pragma once

#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "PhysicWorld.hpp"
#include "Stopwatch.hpp"

class AttackableObject
{
public:
    AttackableObject(const int damage, const int range, const int attackSpeed);

    virtual void update();
    virtual void attack();

    virtual bool canAttack() const;
    virtual int getDamage() const;
    virtual bool isAttack() const;

protected:
    Timer attackTimer;

    int m_damage;
    int m_range;
    int m_attackSpeed;

    bool m_bAttack;
    bool m_bCanAttack;
};
