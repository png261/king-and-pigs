#ifndef PIG_ENEMY_HPP
#define PIG_ENEMY_HPP

#include "Enemy.hpp"

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
