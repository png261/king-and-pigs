#include "Heart.hpp"
#include <iostream>
#include "Collision.hpp"
#include "Game.hpp"

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
    if (Collision::check(this, Game::Instance()->getPlayer())) {
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
