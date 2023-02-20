#include "Heart.hpp"
#include <iostream>
#include "Box2D.hpp"
#include "Game.hpp"

void Heart::load(const LoaderParams* pParams)
{
    ItemObject::load(pParams);

    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
    dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.filter.categoryBits = Box2D::ITEM;
    fixtureDef.filter.maskBits = Box2D::WALL | Box2D::PLAYER;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    m_animations[IDLE] = new Animation("heart idle", 7);
    m_animations[HIT] = new Animation("heart hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Heart::bonus()
{
    Game::Instance()->getPlayer()->changeLives(+1);
    m_curAnimation = HIT;
    m_animations[m_curAnimation]->start();
    /* m_bDead = true; */
}

void Heart::update()
{
    ItemObject::update();
}

void Heart::clean() {}
