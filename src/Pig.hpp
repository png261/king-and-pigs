#pragma once

#include "AttackableObject.hpp"
#include "Enemy.hpp"
#include "Log.hpp"

class Pig : public Enemy, public DamageableObject, public AttackableObject
{
public:
    Pig();
    void load(std::unique_ptr<LoaderParams> const& pParams);
    void loadAnimation();
    void update();
    void updateAnimation();
};
