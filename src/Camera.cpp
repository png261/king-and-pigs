#include "Camera.hpp"
#include <iostream>
#include "Game.hpp"

Camera::Camera()
    : m_pTarget(0)
    , m_position(0, 0)
    , m_zoom(1)
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

float Camera::getZoom() const
{
    return m_zoom;
}

b2Vec2 Camera::getPosition() const
{
    if (m_pTarget == nullptr) {
        return m_position;
    }


    b2Vec2 pos =
        m_pTarget->getPosition() -
        b2Vec2(
            ((Game::Instance()->getWindow()->getWidth() - m_pTarget->getWidth()) / m_zoom / 2.0f),
            ((Game::Instance()->getWindow()->getHeight() - m_pTarget->getHeight()) / m_zoom /
             2.0f));

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

void Camera::setZoom(float zoom)
{
    m_zoom = zoom;
    SDL_RenderSetScale(TheGame::Instance()->getWindow()->getRenderer(), m_zoom, m_zoom);
}
