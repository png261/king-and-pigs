#include "DamageableObject.hpp"
#include <iostream>

DamageableObject::DamageableObject(const int initialHp, const int invulnerableTime)
    : m_hp(initialHp)
    , m_bDead(false)
    , m_bInvulnerable(false)
    , m_invulnerableTime(invulnerableTime)
{}

void DamageableObject::heal(const int d)
{
    m_hp += d;
}

bool DamageableObject::isDead() const
{
    return m_bDead;
}

bool DamageableObject::isInvulnerable() const
{
    return m_bInvulnerable;
}

void DamageableObject::startInvulnerable()
{
    if (this->isInvulnerable() || this->isDead()) {
        return;
    }

    m_bInvulnerable = true;
    invulnerableTimer.start();
};

void DamageableObject::stopInvulnerable()
{
    m_bInvulnerable = false;
    invulnerableTimer.stop();
};

void DamageableObject::damage(const int d)
{
    if (this->isInvulnerable() || this->isDead()) {
        return;
    }

    m_hp -= d;
    if (m_hp <= 0) {
        m_hp = 0;
        m_bDead = true;
        deadTimer.start();
        return;
    }

    this->startInvulnerable();
};

void DamageableObject::update()
{
    if (invulnerableTimer.delta() >= m_invulnerableTime) {
        this->stopInvulnerable();
    }
};

int DamageableObject::getHp() const
{
    return m_hp;
};
