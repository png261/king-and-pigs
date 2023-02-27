#ifndef DAMAGEABLE_OBJECT_HPP
#define DAMAGEABLE_OBJECT_HPP
#include "GameObject.hpp"
#include "LoaderParams.hpp"
#include "Timer.hpp"

class DamageableObject
{
public:
    DamageableObject(int initialHp, int invulnerableTime);

    virtual void update();

    virtual void heal(int d);
    virtual void damage(int d);
    virtual int getHp();
    virtual bool isDead();
    virtual bool isInvulnerable();

protected:
    Timer invulnerableTimer;
    Timer deadTimer;
    virtual void startInvulnerable();
    virtual void stopInvulnerable();

    bool m_bDead;
    bool m_bInvulnerable;
    int m_invulnerableTime;
    int m_hp;
};

#endif
