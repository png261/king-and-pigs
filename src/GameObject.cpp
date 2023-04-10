#include "GameObject.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

GameObject::GameObject()
    : PhysicObject()
    , m_width(0)
    , m_height(0)
    , m_bExist(true)
    , m_bFlipped(false)
    , m_direction(RIGHT)
{}

GameObject::~GameObject() {}

void GameObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    m_width = pParams->width();
    m_height = pParams->height();
}

void GameObject::loadAnimation(){};

void GameObject::draw()
{
    b2Vec2 halfSize =
        0.5 *
        b2Vec2(m_animations[m_curAnimation]->getWidth(), m_animations[m_curAnimation]->getHeight());

    m_animations[m_curAnimation]->draw(
        getPosition() - halfSize - Camera::Instance()->getPosition(),
        getAngle(),
        m_bFlipped,
        Camera::Instance()->getZoom());
}

void GameObject::update()
{
    PhysicObject::update();
    m_animations[m_curAnimation]->update();
}

void GameObject::updateAnimation() {}

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
