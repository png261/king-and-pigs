#include "DoorObject.hpp"


DoorObject::DoorObject()
    : GameObject()
{}

void DoorObject::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);
    m_animations[Animation::IDLE] = new Animation("door idle", 1);
    m_animations[Animation::DOOR_OPEN] = new Animation("door open", 5);
    m_animations[Animation::DOOR_CLOSE] = new Animation("door close", 5);
    m_pFixture->SetSensor(true);
    m_pBody->SetGravityScale(0);

    m_curAnimation = Animation::DOOR_OPEN;
    m_animations[m_curAnimation]->start();
}

void DoorObject::update()
{
    GameObject::update();
}
