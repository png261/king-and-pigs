#ifndef PLATFORMER_OBJECT_HPP
#define PLATFORMER_OBJECT_HPP

#include "GameObject.hpp"

class PlatformerObject : public GameObject
{
public:
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

    virtual ~PlatformerObject() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean() {}
    virtual std::string type();

    virtual int getLives();
    virtual int getDamageRange();

    virtual void setLives(int lives);
    virtual void setCurrentState(objectMotion state);
    virtual void changeLives(int lives);

    virtual bool isAttack();
    virtual bool isInvulnerable();
    virtual bool isFlipped();

    virtual void attack(PlatformerObject* pTarget);
    virtual void hit(int damage);


    bool invulnerable();

protected:
    PlatformerObject();

    bool checkCollideTile(Vector2D newPos);

    void handleMovement(Vector2D velocity);

    int m_moveSpeed;
    int m_jumpSpeed;

    int m_aniCounter;

    int m_damage;
    int m_damageRange;
    int m_lives;
    int m_maxLives;

    Uint32 m_startState;
    int m_attackSpeed;

    bool m_bInvulnerable;
    bool m_bFlipped;
    bool m_bAttack;

    objectMotion m_currentState;
    objectStatus m_currentAttackState;

    std::vector<std::string> m_animationMap;
};

#endif
