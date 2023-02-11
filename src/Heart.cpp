#include "Heart.h"
#include <iostream>
#include "Collision.h"
#include "Game.h"

Heart::Heart()
    : PlatformerObject()
{}

void Heart::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);
    m_currentState = ON_GROUND;
}

void Heart::update()
{
    switch (m_currentState) {
    case ON_GROUND:
        setAnimation("heart idle");
        if (checkCollision(this, Game::Instance()->getPlayer())) {
            m_currentState = ON_HIT;
            Game::Instance()->getPlayer()->setLives(Game::Instance()->getPlayer()->getLives() + 1);
            m_bDead = true;
        }
        break;
    case ON_HIT: setAnimation("heart hit"); break;
    }
    PlatformerObject::update();
}
void Heart::draw()
{
    PlatformerObject::draw();
}

void Heart::clean() {}
