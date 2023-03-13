#pragma once
#include "GameObject.hpp"
#include "LoaderParams.hpp"
#include "Stopwatch.hpp"
#include "Timer.hpp"

class DamageableObject
{
public:
    DamageableObject(const int initialHp, const int invulnerableTime, const int dyingTime);

    virtual void update();

    virtual void heal(const int d);
    virtual void damage(const int d);

    virtual int getHp() const;
    virtual bool isDying() const;
    virtual bool isDead() const;
    virtual bool isInvulnerable() const;

protected:
    virtual void startInvulnerable();
    virtual void stopInvulnerable();

    Timer invulnerableTimer;
    Timer dyingTimer;

    bool m_bDead;
    bool m_bDying;
    bool m_bInvulnerable;
    int m_invulnerableTime;
    int m_hp;
    int m_dyingTime;
};
