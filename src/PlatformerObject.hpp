#ifndef PLATFORMER_OBJECT_HPP
#define PLATFORMER_OBJECT_HPP

#include <iostream>
#include "GameObject.hpp"

enum objectMotion {
    ON_GROUND,
    ON_FLY,
    ON_FALL,
};

enum objectStatus {
    ON_NORMAL,
    ON_HPPIT,
    ON_ATTACK,
    ON_DIE,
};


class PlatformerObject : public GameObject
{
public:
    virtual ~PlatformerObject() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();

    virtual void clean() {}

    virtual std::string type() { return "GameObject"; }
    virtual bool isInvulnerable() { return m_bInvulnerable; }

    virtual void setLives(int lives) { m_lives = std::max(std::min(lives, m_maxLives), 0); }
    virtual void changeLives(int lives) { setLives(m_lives + lives); }

    virtual int getLives() { return m_lives; }

    virtual void hit(int damage)
    {
        if (m_bInvulnerable == true) {
            return;
        }

        m_currentAttackState = ON_HPPIT;
        changeLives(-damage);
    };
    virtual void attack(PlatformerObject* pTarget) { pTarget->hit(1); };
    virtual bool isAttack() { return m_bAttack; }
    virtual int getDamageRange() { return m_damageRange; }
    virtual bool getFlipped() { return m_bFlipped; }

    void setCurrentState(objectMotion state) { m_currentState = state; }
    bool invulnerable() { return m_bInvulnerable; }

protected:
    PlatformerObject();

    bool checkCollideTile(Vector2D newPos);

    void handleMovement(Vector2D velocity);

    int m_moveSpeed;
    int m_jumpSpeed;

    bool m_bInvulnerable;
    int m_aniCounter;

    bool m_bFlipped;

    int m_damage;
    int m_damageRange;
    bool m_bAttack;
    int m_lives;
    int m_maxLives;

    Uint32 m_startState;
    int m_attackSpeed;

    std::vector<std::string> m_animationMap;

    objectMotion m_currentState;
    objectStatus m_currentAttackState;
};

#endif
