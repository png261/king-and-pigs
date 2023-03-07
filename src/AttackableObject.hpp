#pragma once

#include "Box2D.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"

class AttackableObject
{
public:
    AttackableObject(const int damage, const int range, const int attackSpeed);

    virtual void createAttackSensor(
        b2Body* const pBody,
        const int objectWidth,
        const Box2D::FilterMask filterMask);

    virtual void update();
    virtual void attack();

    virtual bool canAttack() const;
    virtual int getDamage() const;
    virtual bool isAttack() const;
    virtual bool isTurnRight() const;

protected:
    Timer attackTimer;

    int m_damage;
    int m_range;
    int m_attackSpeed;

    bool m_bAttack;
    bool m_bCanAttack;
    bool m_bTurnRight;

    b2Fixture* m_pAttackSensor;
};


