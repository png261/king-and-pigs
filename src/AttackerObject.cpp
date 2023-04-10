#include "AttackerObject.hpp"
#include "PhysicWorld.hpp"

AttackerObject::AttackerObject(const int damage, const int range, const int attackSpeed)
    : m_attackDamage(damage)
    , m_attackRange(range)
    , m_attackSpeed(attackSpeed)
    , attackTimer(100)
    , delayTimer(attackSpeed)
    , m_bAttacking(false)
    , m_bDaming(false)
    , m_bCanAttack(true)
{}

bool AttackerObject::isAttack() const
{
    return m_bAttacking;
}

bool AttackerObject::canAttack() const
{
    return m_bCanAttack;
}

int AttackerObject::getDamage() const
{
    return m_attackDamage;
}

void AttackerObject::attack()
{
    if (isAttack() || !canAttack()) {
        return;
    }

    m_bAttacking = true;
    m_bDaming = true;
    m_bCanAttack = false;
    attackTimer.start();
    delayTimer.start();
}

void AttackerObject::update()
{
    if (attackTimer.isDone()) {
        m_bDaming = false;
    }

    if (delayTimer.isDone()) {
        m_bCanAttack = true;
        m_bAttacking = false;
    }
}

bool AttackerObject::isDaming() const
{
    return m_bDaming;
}
