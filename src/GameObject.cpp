#include "GameObject.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

GameObject::GameObject()
    : PhysicObject()
    , m_width(0)
    , m_height(0)
    , m_bUpdating(false)
    , m_bExist(true)
    , m_bFlipped(false)
{}

GameObject::~GameObject()
{
    m_animations.clear();
}

void GameObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    m_width = pParams->width();
    m_height = pParams->height();
}

void GameObject::loadAnimation(){};

void GameObject::draw()
{
    m_animations[m_curAnimation]->draw(
        this->getPosition() - Camera::Instance()->getPosition(),
        this->getAngle(),
        m_bFlipped);
}

void GameObject::update()
{
    PhysicObject::update();
    m_animations[m_curAnimation]->update();
}

void GameObject::updateAnimation() {}

bool GameObject::isUpdating() const
{
    return m_bUpdating;
}

void GameObject::setUpdating(const bool bUpdating)
{
    m_bUpdating = bUpdating;
}

bool GameObject::isExist() const
{
    return m_bExist;
}

void GameObject::disappear()
{
    m_bExist = false;
}

int GameObject::getWidth() const
{
    return m_width;
}

int GameObject::getHeight() const
{
    return m_height;
}
