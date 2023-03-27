#include "AttackerObject.hpp"
#include "PhysicWorld.hpp"

AttackerObject::AttackerObject(const int damage, const int range, const int attackSpeed)
    : m_attackDamage(damage)
    , m_attackRange(range)
    , m_attackSpeed(attackSpeed)
    , attackTimer(attackSpeed)
    , m_bAttack(false)
    , m_bCanAttack(true)
{}

bool AttackerObject::isAttack() const
{
    return m_bAttack;
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
    if (this->isAttack() || this->canAttack() == false) {
        return;
    }

    m_bAttack = true;
    m_bCanAttack = false;
    attackTimer.start();
}

void AttackerObject::update()
{
    if (attackTimer.isDone()) {
        m_bAttack = false;
        m_bCanAttack = true;
    }
}
