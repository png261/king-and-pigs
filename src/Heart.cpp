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
    if (checkCollision(this, Game::Instance()->getPlayer())) {
        Game::Instance()->getPlayer()->setLives(Game::Instance()->getPlayer()->getLives() + 1);
        m_bDead = true;
    }
    PlatformerObject::update();
}
void Heart::draw()
{
    PlatformerObject::draw();
}

void Heart::clean() {}
