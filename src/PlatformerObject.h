#ifndef PLATFORMER_OBJECT_H
#define PLATFORMER_OBJECT_H

#include "GameObject.h"

class PlatformerObject : public GameObject {
  public:
    virtual ~PlatformerObject() {}

    virtual void load(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();

    virtual void clean() {}
    virtual void collision() {}

    virtual std::string type() { return "SDLGameObject"; }

  protected:
    PlatformerObject();

    void doDyingAnimation();

    int m_moveSpeed;

    // how long the death animation takes, along with a counter
    int m_dyingTime;
    int m_dyingCounter;
    
    // has the explosion sound played?
    bool m_bPlayedDeathSound;
    
    bool m_bFlipped;
    
    bool m_bMoveLeft;
    bool m_bMoveRight;
    bool m_bRunning;
    
    bool m_bFalling;
    bool m_bJumping;
    bool m_bCanJump;
    
    Vector2D m_lastSafePos;
    
    int m_jumpHeight;
};

#endif
