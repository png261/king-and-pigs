#pragma once

#include "Timer.hpp"

class AttackerObject
{
public:
    AttackerObject(const int damage, const int range, const int speed);

    virtual void update();
    virtual void attack();

    virtual bool canAttack() const;
    virtual int getDamage() const;
    virtual bool isAttack() const;
    virtual bool isDaming() const;

    virtual int getAttackDamage();
    virtual int getAttackRange();
    virtual int getAttackSpeed();

protected:
    int attack_damage_;
    int attack_range_;
    int attack_speed_;

    Timer attack_timer_;
    Timer delay_timer_;

    bool is_attacking_;
    bool is_daming_;
    bool can_attack_;
};
