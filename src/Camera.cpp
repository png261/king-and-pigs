#include "Camera.hpp"
#include "Game.hpp"

Camera::Camera()
    : m_pTarget(0)
    , m_position(0, 0)
{}

Camera::~Camera()
{
    delete m_pTarget;
}

Camera* Camera::Instance()
{
    static Camera* s_pCamera = new Camera();
    return s_pCamera;
}

b2Vec2 Camera::getPosition() const
{
    if (m_pTarget == nullptr) {
        return m_position;
    }

    b2Vec2 pos(
        m_pTarget->getPosition().x -
            ((Game::Instance()->getGameWidth() - m_pTarget->getWidth()) / 2.0),
        m_pTarget->getPosition().y -
            ((Game::Instance()->getGameHeight() - m_pTarget->getHeight()) / 2.0));

    if (pos.x < 0) {
        pos.x = 0;
    }

    return pos;
}

void Camera::update()
{
    m_position = m_pTarget->getPosition();

    if (m_position.x < 0) {
        m_position.x = 0;
    }

    if (m_position.y < 0) {
        m_position.y = 0;
    }
}

void Camera::setTarget(GameObject* target)
{
    m_pTarget = target;
}

void Camera::setPosition(const b2Vec2& position)
{
    m_position = position;
}
