#ifndef EMENY_HPP
#define EMENY_HPP

#include <iostream>
#include "Collision.hpp"
#include "Game.hpp"
#include "PlatformerObject.hpp"

class Enemy : public PlatformerObject
{
public:
    virtual std::string type() { return "Enemy"; }
    virtual void load(const LoaderParams* pParams) { PlatformerObject::load(pParams); };
    virtual void draw() { PlatformerObject::draw(); }
    virtual void update()
    {
        PlatformerObject::update();
        if (Game::Instance()->getPlayer()->isAttack() &&
            Collision::checkAttack(
                Game::Instance()->getPlayer(),
                this,
                Game::Instance()->getPlayer()->getDamageRange())) {
            hit(1);
        }
        if (m_bAttack && Collision::check(Game::Instance()->getPlayer(), this)) {
            Game::Instance()->getPlayer()->hit(1);
        }
    }

protected:
    Enemy()
        : PlatformerObject()
    {}
};

#endif
