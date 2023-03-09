#pragma once

#include "AttackableObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"

class Player final : public GameObject, public DamageableObject, public AttackableObject
{
public:
    Player();
    void load(const LoaderParams* const pParams);

    void update();
    void updateAnimation();
    void loadAnimation();

private:
    void handleInput();
};
