#ifndef PIG_ENEMY_HPP
#define PIG_ENEMY_HPP

#include "AttackableObject.hpp"
#include "Enemy.hpp"

class Pig : public Enemy, public DamageableObject, public AttackableObject
{
public:
    Pig();
    void load(const LoaderParams* const pParams);
    void draw();
    void update();
    void updateAnimation();
};

#endif
