#ifndef PLATFORMER_OBJECT_H
#define PLATFORMER_OBJECT_H

#include "GameObject.h"

enum object_state {
    ON_GROUND,
    ON_FLY,
    ON_FALL,
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

    virtual void onHit(){};

    virtual std::string type() { return "GameObject"; }
    virtual bool isInvulnerable() { return m_bInvulnerable; }

    virtual void setLives(int lives) { m_lives = std::max(std::min(lives, m_maxLives), 0); }

    virtual int getLives() { return m_lives; }

    void setCurrentState(object_state state) { m_currentState = state; }

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
    int m_lives;
    int m_maxLives;

    object_state m_currentState;
};

#endif
