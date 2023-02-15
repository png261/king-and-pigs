#ifndef EMENY_H
#define EMENY_H

#include <iostream>
#include "Collision.h"
#include "Game.h"
#include "PlatformerObject.h"

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
            checkCollisionAttack(
                Game::Instance()->getPlayer(),
                this,
                Game::Instance()->getPlayer()->getDamageRange())) {
            hit(1);
        }
        if (m_bAttack && checkCollision(Game::Instance()->getPlayer(), this)) {
            Game::Instance()->getPlayer()->hit(1);
        }
    }

protected:
    Enemy()
        : PlatformerObject()
    {}
};

#endif
