#include "Door.hpp"


Door::Door()
    : GameObject()
{}

void Door::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_DOOR;
    filter.maskBits = Box2D::MASK_DOOR;
    m_pFixture->SetFilterData(filter);

    this->loadAnimation();
}

void Door::loadAnimation()
{
    m_animations[Animation::IDLE] = new Animation("door idle", 78, 96, 1);
    m_animations[Animation::DOOR_OPEN] = new Animation("door open", 78, 96, 5);
    m_animations[Animation::DOOR_CLOSE] = new Animation("door close", 78, 96, 5);

    m_curAnimation = Animation::DOOR_OPEN;
    m_animations[m_curAnimation]->start();
}

void Door::update()
{
    GameObject::update();
}
