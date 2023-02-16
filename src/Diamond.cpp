#include "Diamond.hpp"
#include <iostream>
#include "Collision.hpp"
#include "Game.hpp"

void Diamond::load(const LoaderParams* pParams)
{
    ItemObject::load(pParams);

    m_animations[IDLE] = new Animation("diamond idle", 7);
    m_animations[HIT] = new Animation("diamond hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Diamond::bonus()
{
    Game::Instance()->getPlayer()->changeLives(+1);
}

void Diamond::update()
{
    if (Collision::check(this, Game::Instance()->getPlayer())) {
        bonus();
        m_animations[m_curAnimation]->stop();
        m_curAnimation = HIT;
        m_animations[m_curAnimation]->start();
        m_bDead = true;
    }

    ItemObject::update();
}

void Diamond::clean() {}
