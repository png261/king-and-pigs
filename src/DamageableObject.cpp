#include "DamageableObject.hpp"

DamageableObject::DamageableObject(
    const int initialHp,
    const int invulnerableTime,
    const int dyingTime)
    : m_hp(initialHp)
    , m_bDead(false)
    , m_bDying(false)
    , m_bInvulnerable(false)
    , m_invulnerableTime(invulnerableTime)
    , m_dyingTime(dyingTime)
    , invulnerableTimer(invulnerableTime)
    , dyingTimer(dyingTime)
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
};

void DamageableObject::damage(const int d)
{
    if (this->isInvulnerable() || this->isDead()) {
        return;
    }

    m_hp -= d;
    if (m_hp <= 0) {
        m_hp = 0;
        m_bDying = true;
        dyingTimer.start();
        return;
    }

    this->startInvulnerable();
};

void DamageableObject::update()
{
    if (m_bDead) {
        return;
    }

    if (invulnerableTimer.isDone()) {
        this->stopInvulnerable();
    }

    if (m_bDying && dyingTimer.isDone()) {
        m_bDead = true;
    };
}

int DamageableObject::getHp() const
{
    return m_hp;
};

bool DamageableObject::isDying() const
{
    return m_bDying;
}
