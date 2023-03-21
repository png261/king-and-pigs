#include "AttackableObject.hpp"
#include "PhysicWorld.hpp"

AttackableObject::AttackableObject(const int damage, const int range, const int attackSpeed)
    : m_damage(damage)
    , m_range(range)
    , m_bAttack(false)
    , m_bCanAttack(true)
    , m_attackSpeed(attackSpeed)
    , attackTimer(attackSpeed)
{}

bool AttackableObject::isAttack() const
{
    return m_bAttack;
}

bool AttackableObject::canAttack() const
{
    return m_bCanAttack;
}

int AttackableObject::getDamage() const
{
    return m_damage;
}

void AttackableObject::attack()
{
    if (this->isAttack() || this->canAttack() == false) {
        return;
    }

    m_bAttack = true;
    m_bCanAttack = false;
    attackTimer.start();
}

void AttackableObject::update()
{
    if (attackTimer.isDone()) {
        m_bAttack = false;
        m_bCanAttack = true;
    }
}
