#include "AttackerObject.hpp"

#include "PhysicWorld.hpp"

AttackerObject::AttackerObject(const int damage, const int range, const int speed)
    : attack_damage_(damage)
    , attack_range_(range)
    , attack_speed_(speed)
    , attack_timer_(10)
    , delay_timer_(speed)
    , is_attacking_(false)
    , is_daming_(false)
    , can_attack_(true)
{}

bool AttackerObject::isAttack() const
{
    return is_attacking_;
}

bool AttackerObject::canAttack() const
{
    return can_attack_;
}

int AttackerObject::getDamage() const
{
    return attack_damage_;
}

void AttackerObject::attack()
{
    if (isAttack() || !canAttack()) {
        return;
    }

    is_attacking_ = true;
    is_daming_ = true;
    can_attack_ = false;
    attack_timer_.start();
    delay_timer_.start();
}

void AttackerObject::update()
{
    if (attack_timer_.isDone()) {
        is_daming_ = false;
    }

    if (delay_timer_.isDone()) {
        can_attack_ = true;
        is_attacking_ = false;
    }
}

bool AttackerObject::isDaming() const
{
    return is_daming_;
}

int AttackerObject::GetAttackDamage()
{
    return attack_damage_;
}

int AttackerObject::GetAttackRange()
{
    return attack_range_;
}

int AttackerObject::GetAttackSpeed()
{
    return attack_speed_;
}
