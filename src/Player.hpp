#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AttackableObject.hpp"
#include "DamageableObject.hpp"
#include "PlatformerObject.hpp"

class Player : public PlatformerObject, public DamageableObject, public AttackableObject
{
public:
    Player();
    void load(const LoaderParams* const pParams);

    void draw();
    void update();
    void updateAnimation();

    std::string type() const { return "Player"; }

private:
    void handleInput();
    b2Fixture* m_pAttackRange;
};

#endif
