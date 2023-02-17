#include "Box.hpp"

Box::Box()
    : PlatformerObject()
{}

void Box::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);
    m_pBody->SetFixedRotation(false);
    m_animations[IDLE] = new Animation("box idle", 1);
    m_animations[HIT] = new Animation("box hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    PlatformerObject::update();
}
void Box::draw()
{
    PlatformerObject::draw();
}
void Box::collision() {}
void Box::clean() {}
