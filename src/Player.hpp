#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AttackableObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"

class Player : public GameObject, public DamageableObject, public AttackableObject
{
public:
    Player();
    void load(const LoaderParams* const pParams);

    void draw();
    void update();
    void updateAnimation();
    void loadAnimation();

private:
    void handleInput();
    b2Fixture* m_pAttackRange;
};

#endif
