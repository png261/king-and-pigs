#ifndef ATTACK_ABLE_OBJECT_HPP
#define ATTACK_ABLE_OBJECT_HPP

#include "Box2D.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"

class AttackableObject
{
public:
    AttackableObject(int damage, int range, int attackSpeed);

    virtual void createAttackSensor(b2Body* pBody, int objectWidth, Box2D::FilterMask filterMask);

    virtual bool canAttack();
    virtual void update();
    virtual void attack();

    virtual int getDamage();
    virtual bool isAttack();
    virtual bool isTurnRight();

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


#endif
