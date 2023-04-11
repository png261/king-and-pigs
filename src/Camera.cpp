#include "Camera.hpp"
#include <iostream>
#include "Game.hpp"

Camera::Camera()
    : m_pTarget(nullptr)
    , m_position(0, 0)
    , m_zoom(1)
{}

Camera& Camera::Instance()
{
    static Camera s_instance{};
    return s_instance;
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
        m_position -
        0.5 * b2Vec2(
                  Game::Instance().getWindow()->getWidth() / m_zoom - m_pTarget->getWidth(),
                  Game::Instance().getWindow()->getHeight() / m_zoom - m_pTarget->getHeight());

    if (pos.x < 0) {
        pos.x = 0;
    }

    if (pos.y < 0) {
        pos.y = 0;
    }

    return pos;
}

void Camera::update()
{
    Game& game = Game::Instance();
    m_position = m_pTarget->getPosition();

    float maxX = game.getLevel()->getMapWidth() -
                 (game.getWindow()->getWidth() / m_zoom + m_pTarget->getWidth()) * 0.5;
    float maxY = game.getLevel()->getMapHeight() -
                 (game.getWindow()->getHeight() / m_zoom + m_pTarget->getHeight()) * 0.5;

    if (m_position.x > maxX) {
        m_position.x = maxX;
    }

    if (m_position.y > maxY) {
        m_position.y = maxY;
    }


    if (m_position.x < 0) {
        m_position.x = 0;
    }

    if (m_position.y < 0) {
        m_position.y = 0;
    }
}

void Camera::setTarget(GameObject* const target)
{
    m_pTarget = target;
}

void Camera::setPosition(const b2Vec2& position)
{
    m_position = position;
}

void Camera::setZoom(const float zoom)
{
    m_zoom = zoom;
}
