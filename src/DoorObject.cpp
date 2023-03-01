#include "DoorObject.hpp"


DoorObject::DoorObject()
    : PlatformerObject()
{}

void DoorObject::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);
    m_animations[IDLE] = new Animation("door idle", 1);
    m_animations[DOOR_OPEN] = new Animation("door open", 5);
    m_animations[DOOR_CLOSE] = new Animation("door close", 5);
    m_pFixture->SetSensor(true);
    m_pBody->SetGravityScale(0);

    m_curAnimation = DOOR_OPEN;
    m_animations[m_curAnimation]->start();
}

std::string DoorObject::type() const
{
    return "Door";
}

void DoorObject::update()
{
    PlatformerObject::update();
}
