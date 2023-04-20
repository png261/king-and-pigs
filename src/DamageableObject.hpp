#pragma once
#include "GameObject.hpp"
#include "LoaderParams.hpp"
#include "Stopwatch.hpp"
#include "Timer.hpp"

class DamageableObject
{
public:
    DamageableObject(const int hp, const int invulnerab_time, const int dying_time);

    virtual void update();

    virtual void heal(const int n);
    virtual void damage(const int n);

    virtual int getHp() const;
    virtual bool isDying() const;
    virtual bool isDead() const;
    virtual bool isInvulnerable() const;

protected:
    virtual void startInvulnerable();
    virtual void stopInvulnerable();

    int hp_;
    int max_hp_;
    int dying_time_;
    int invulnerable_time_;

    Timer invulnerable_timer_;
    Timer dying_timer_;

    bool is_dead_;
    bool is_dying_;
    bool is_invulnerable_;
};
