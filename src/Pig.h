#ifndef PIG_ENEMY_H
#define PIG_ENEMY_H

#include "Enemy.h"

class Pig : public Enemy
{
public:
    Pig();
    virtual void load(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif
