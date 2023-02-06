#ifndef PIG_ENEMY_H
#define PIG_ENEMY_H

#include "Enemy.h"

enum pig_state {
    PIG_ON_GROUND,
    PIG_ON_FLY,
};

class Pig : public Enemy {
  public:
    Pig();
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void colision();

  private:
    pig_state m_currentState;
};

#endif
