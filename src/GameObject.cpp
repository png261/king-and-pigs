#include "GameObject.hpp"

#include "Game.hpp"


GameObject::GameObject()
    : m_position(0, 0)
    , m_width(0)
    , m_height(0)
    , m_textureHeight(0)
    , m_textureWidth(0)
    , m_bUpdating(false)
    , m_angle(0)
    , m_bDead(false)
    , m_bFlipped(false)
{}

void GameObject::load(const LoaderParams* pParams)
{
    m_position = b2Vec2(pParams->getX(), pParams->getY());

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();

    m_textureWidth = pParams->getTextureWidth();
    m_textureHeight = pParams->getTextureHeight();
    m_textureX = pParams->getTextureX();
    m_textureY = pParams->getTextureY();
}


b2Vec2& GameObject::getPosition()
{
    return m_position;
}

int GameObject::getWidth() const
{
    return m_width;
}

int GameObject::getHeight() const
{
    return m_height;
}

b2Body* GameObject::getBody() const
{
    return m_pBody;
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
