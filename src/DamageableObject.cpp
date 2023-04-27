#include "DamageableObject.hpp"

DamageableObject::DamageableObject(const int hp, const int invulnerab_time, const int dying_time)
    : hp_(hp)
    , max_hp_(hp)
    , dying_time_(dying_time)
    , invulnerable_time_(invulnerab_time)
    , invulnerable_timer_(invulnerab_time)
    , dying_timer_(dying_time)
    , is_dead_(false)
    , is_dying_(false)
    , is_invulnerable_(false)
{}

void DamageableObject::heal(const int n)
{
    hp_ += n;
    hp_ = std::max(0, std::min(max_hp_, hp_));
}

bool DamageableObject::isDead() const
{
    return is_dead_;
}

bool DamageableObject::isInvulnerable() const
{
    return is_invulnerable_;
}

void DamageableObject::startInvulnerable()
{
    if (isInvulnerable() || isDead()) {
        return;
    }

    is_invulnerable_ = true;
    invulnerable_timer_.start();
};

void DamageableObject::stopInvulnerable()
{
    is_invulnerable_ = false;
};

void DamageableObject::damage(const int n)
{
    if (isInvulnerable() || isDead()) {
        return;
    }

    hp_ -= n;
    if (hp_ <= 0) {
        hp_ = 0;
        is_dying_ = true;
        dying_timer_.start();
        return;
    }

    startInvulnerable();
};

void DamageableObject::update()
{
    if (is_dead_) {
        return;
    }

    if (invulnerable_timer_.isDone()) {
        stopInvulnerable();
    }

    if (is_dying_ && dying_timer_.isDone()) {
        is_dead_ = true;
    };
}

int DamageableObject::getHp() const
{
    return hp_;
};

int DamageableObject::getMaxHp() const
{
    return max_hp_;
};

bool DamageableObject::isDying() const
{
    return is_dying_;
}
