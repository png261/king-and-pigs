#ifndef DAMAGEABLE_OBJECT_HPP
#define DAMAGEABLE_OBJECT_HPP
#include "GameObject.hpp"
#include "LoaderParams.hpp"
#include "Timer.hpp"

class DamageableObject
{
public:
    DamageableObject(const int initialHp, const int invulnerableTime);

    virtual void update();

    virtual void heal(const int d);
    virtual void damage(const int d);

    virtual int getHp() const;
    virtual bool isDead() const;
    virtual bool isInvulnerable() const;

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
