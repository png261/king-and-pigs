#include "Heart.hpp"
#include <iostream>
#include "Box2D.hpp"
#include "Game.hpp"

void Heart::load(const LoaderParams* pParams)
{
    ItemObject::load(pParams);

    m_animations[IDLE] = new Animation("heart idle", 7);
    m_animations[HIT] = new Animation("heart hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Heart::bonus()
{
    m_curAnimation = HIT;
    m_animations[m_curAnimation]->start();
    m_bExist = false;
}

void Heart::update()
{
    ItemObject::update();
}

void Heart::clean() {}
