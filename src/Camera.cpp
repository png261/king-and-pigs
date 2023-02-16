#include "Camera.hpp"
#include <iostream>
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

Vector2D Camera::getPosition() const
{
    if (m_pTarget == NULL) {
        return m_position;
    }

    Vector2D pos(
        m_pTarget->getPosition().m_x -
            ((Game::Instance()->getGameWidth() - m_pTarget->getWidth()) / 2.0),
        m_pTarget->getPosition().m_y -
            ((Game::Instance()->getGameHeight() - m_pTarget->getHeight()) / 2.0));

    if (pos.m_x < 0) {
        pos.m_x = 0;
    }

    return pos;
}

void Camera::update()
{
    m_position += m_pTarget->getVelocity();

    if (m_position.m_x < 0) {
        m_position.m_x = 0;
    }
    if (m_position.m_y < 0) {
        m_position.m_y = 0;
    }

    if (m_position.m_y < 0) {
        m_position.m_y = 0;
    }
}
