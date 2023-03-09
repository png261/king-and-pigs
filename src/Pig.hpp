#pragma once

#include "AttackableObject.hpp"
#include "Enemy.hpp"

class Pig : public Enemy, public DamageableObject, public AttackableObject
{
public:
    Pig();
    void load(const LoaderParams* const pParams);
    void update();
    void updateAnimation();
    void loadAnimation();
};
