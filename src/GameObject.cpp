#include "GameObject.hpp"
GameObject::GameObject()
    : m_position(0, 0)
    , m_velocity(0, 0)
    , m_acceleration(0, 0)
    , m_width(0)
    , m_height(0)
    , m_textureHeight(0)
    , m_textureWidth(0)
    , m_bUpdating(false)
    , m_angle(0)
    , m_bDead(false)
    , m_bFlipped(false)
{}

Vector2D& GameObject::getPosition()
{
    return m_position;
}
Vector2D& GameObject::getVelocity()
{
    return m_velocity;
}

int GameObject::getWidth() const
{
    return m_width;
}
int GameObject::getHeight() const
{
    return m_height;
}

bool GameObject::isUpdating() const
{
    return m_bUpdating;
}

void GameObject::setUpdating(bool updating)
{
    m_bUpdating = updating;
}

bool GameObject::isDead() const
{
    return m_bDead;
}

void GameObject::setCollisionLayers(std::vector<TileLayer*>* layers)
{
    m_pCollisionLayers = layers;
}
