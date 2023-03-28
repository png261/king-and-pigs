#include "Door.hpp"

Door::Door()
    : GameObject()
    , m_bOpened(false)
{}

void Door::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);

    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);

    this->loadAnimation();
}

void Door::loadAnimation()
{
    m_animations[DOOR_CLOSED] = new Animation("door idle", 46, 56, 1);
    m_animations[DOOR_OPENING] = new Animation("door open", 46, 56, 5, false);
    m_animations[DOOR_CLOSING] = new Animation("door close", 46, 56, 5, false);

    m_curAnimation = DOOR_CLOSED;
    m_animations[m_curAnimation]->start();
}

void Door::update()
{
    GameObject::update();
}

void Door::open()
{
    if (this->isOpened()) {
        return;
    }

    m_curAnimation = DOOR_OPENING;
    m_animations[m_curAnimation]->start();
    if (m_animations[DOOR_OPENING]->isFinished()) {
        m_bOpened = true;
    }
}

void Door::close()
{
    if (this->isClosed()) {
        return;
    }

    m_curAnimation = DOOR_CLOSING;
    m_animations[m_curAnimation]->start();
    if (m_animations[DOOR_CLOSING]->isFinished()) {
        m_bOpened = false;
    }
}

bool Door::isOpened() const
{
    return m_bOpened;
}

bool Door::isClosed() const
{
    return !m_bOpened;
}
