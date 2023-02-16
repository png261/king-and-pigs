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
    ON_HIT,
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
    virtual std::string type();

    virtual int getLives();
    virtual int getDamageRange();
    virtual bool isFlipped();

    virtual void setLives(int lives);
    virtual void setCurrentState(objectMotion state);
    virtual void changeLives(int lives);

    virtual bool isAttack();
    virtual bool isInvulnerable();

    virtual void attack(PlatformerObject* pTarget);
    virtual void hit(int damage);


    bool invulnerable();

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
