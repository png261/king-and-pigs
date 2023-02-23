#include "Box.hpp"
#include "Box2D.hpp"

Box::Box()
    : Enemy()
{}

void Box::load(const LoaderParams* pParams)
{
    Enemy::load(pParams);

    m_pBody->SetFixedRotation(false);
    m_animations[IDLE] = new Animation("box idle", 1);
    m_animations[HIT] = new Animation("box hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    Enemy::update();
}

void Box::draw()
{
    Enemy::draw();
}

void Box::clean() {}
