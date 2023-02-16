#include "GameObject.hpp"
GameObject::GameObject()
    : m_position(0, 0)
    , m_velocity(0, 0)
    , m_acceleration(0, 0)
    , m_width(0)
    , m_height(0)
    , m_textureHeight(0)
    , m_textureWidth(0)
    , m_currentRow(0)
    , m_currentFrame(0)
    , m_bUpdating(false)
    , m_angle(0)
    , m_bDead(false)
    , m_alpha(255)
    , m_bFlipped(false)
    , m_aniCounter(false)
{
    m_numFrames = TextureManager::Instance()->getNFrames(m_textureID);
}

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

void GameObject::setAnimation(std::string textureID)
{
    m_textureID = textureID;
    m_numFrames = TextureManager::Instance()->getNFrames(textureID);
}

bool GameObject::isUpdating()
{
    return m_bUpdating;
}

void GameObject::setUpdating(bool updating)
{
    m_bUpdating = updating;
}

bool GameObject::isDead()
{
    return m_bDead;
}

void GameObject::setCollisionLayers(std::vector<TileLayer*>* layers)
{
    m_pCollisionLayers = layers;
}
