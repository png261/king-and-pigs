#include "Door.hpp"
#include "Log.hpp"
#include "SoundManager.hpp"

Door::Door()
    : GameObject()
    , m_bOpened(false)
{}

void Door::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    createBody(pParams->x(), pParams->y(), m_width, m_height);

    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);

    loadAnimation();
}

void Door::loadAnimation()
{
    m_animations[DOOR_CLOSED] = std::make_unique<Animation>("door idle", 46, 56, 1);
    m_animations[DOOR_OPENING] = std::make_unique<Animation>("door open", 46, 56, 5, false);
    m_animations[DOOR_CLOSING] = std::make_unique<Animation>("door close", 46, 56, 3, false);

    m_curAnimation = DOOR_CLOSED;
    m_animations[m_curAnimation]->start();
}

void Door::update()
{
    GameObject::update();
    if (m_curAnimation == DOOR_CLOSING && m_animations[DOOR_CLOSING]->isFinished()) {
        SoundManager::Instance().playSFX("door close");
        m_bOpened = false;
    }

    if (m_curAnimation == DOOR_OPENING && m_animations[DOOR_OPENING]->isFinished()) {
        SoundManager::Instance().playSFX("door open");
        m_bOpened = true;
    }
}

void Door::open()
{
    if (isOpened()) {
        return;
    }

    m_curAnimation = DOOR_OPENING;
    m_animations[m_curAnimation]->start();
}

void Door::close()
{
    if (isClosed()) {
        return;
    }

    m_curAnimation = DOOR_CLOSING;
    m_animations[m_curAnimation]->start();
}

bool Door::isOpened() const
{
    return m_bOpened;
}

bool Door::isClosed() const
{
    return !m_bOpened;
}
