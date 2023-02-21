#ifndef PLATFORMER_OBJECT_HPP
#define PLATFORMER_OBJECT_HPP

#include <iostream>
#include "Animation.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"

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

    enum ANIMATION_ID {
        IDLE,
        RUN,
        JUMP,
        FALL,
        GROUND,
        ATTACK,
        DEAD,
        HIT,
        DOOR_IN,
        DOOR_OUT,
    };

    virtual ~PlatformerObject() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean() {}
    virtual std::string type() const;

    virtual int getLives() const;
    virtual int getDamageRange() const;

    virtual void setLives(int lives);
    virtual void setCurrentState(objectMotion state);
    virtual void changeLives(int lives);

    virtual bool isAttack() const;
    virtual bool isInvulnerable() const;
    virtual bool isFlipped() const;

    virtual void attack(PlatformerObject* pTarget);
    virtual void hit(int damage);
    virtual void changeFootContact(int n) { m_footContact += n; }

protected:
    PlatformerObject();

    bool checkCollideTile(b2Vec2 newPos);

    void handleMovement(b2Vec2 velocity);

    int m_moveSpeed;
    int m_jumpSpeed;

    int m_damage;
    int m_damageRange;
    int m_lives;
    int m_maxLives;

    int m_attackSpeed;

    bool m_bInvulnerable;
    bool m_bFlipped;
    bool m_bAttack;

    objectMotion m_currentState;
    objectStatus m_currentAttackState;

    std::vector<std::string> m_animationMap;
    std::map<ANIMATION_ID, Animation*> m_animations;
    ANIMATION_ID m_curAnimation;
    Timer timer;
    b2Body* m_pBody;
    b2Fixture* m_pFixture;
    int m_footContact;
};

#endif
