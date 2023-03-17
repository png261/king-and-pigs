#include "Door.hpp"
#include "Log.hpp"


Door::Door()
    : GameObject()
{}

void Door::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);

    this->loadAnimation();
}

void Door::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("door idle", 46, 56, 1));
    m_animations[Animation::DOOR_OPEN] =
        std::make_unique<Animation>(Animation("door open", 46, 56, 5, false));
    m_animations[Animation::DOOR_CLOSE] =
        std::make_unique<Animation>(Animation("door close", 46, 56, 5, false));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Door::update()
{
    GameObject::update();
}

void Door::open()
{
    m_curAnimation = Animation::DOOR_OPEN;
    m_animations[m_curAnimation]->start();
}

void Door::close()
{
    m_curAnimation = Animation::DOOR_CLOSE;
    m_animations[m_curAnimation]->start();
}
