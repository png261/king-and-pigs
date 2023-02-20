#include "PlatformerObject.hpp"
#include <iostream>

#include "Box2D.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

PlatformerObject::PlatformerObject()
    : GameObject()
    , m_bAttack(false)
    , m_bInvulnerable(false)
    , m_footContact(0)
{}

void PlatformerObject::load(const LoaderParams* pParams)
{
    GameObject::load(pParams);
    m_lives = pParams->getLives();
    m_maxLives = m_lives;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_position.getX(), m_position.getY());
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = Box2D::Instance()->getWorld()->CreateBody(&bodyDef);
}

void PlatformerObject::draw()
{
    m_animations[m_curAnimation]->draw(
        m_position.getX() + m_textureX - TheCamera::Instance()->getPosition().m_x,
        m_position.getY() + m_textureY - TheCamera::Instance()->getPosition().m_y,
        m_textureWidth,
        m_textureHeight,
        m_pBody->GetAngle() / 3.14 * 180,
        m_bFlipped);
}

void PlatformerObject::update()
{
    b2Vec2 newPosition = m_pBody->GetPosition();
    m_position.setX(newPosition.x);
    m_position.setY(newPosition.y);

    if (getLives() <= 0) {
        m_currentAttackState = ON_DIE;
    }

    m_velocity += m_acceleration;

    if (m_velocity.getX() < 0) {
        m_bFlipped = true;
    } else if (m_velocity.getX() > 0) {
        m_bFlipped = false;
    }
}

std::string PlatformerObject::type()
{
    return "GameObject";
}

bool PlatformerObject::isInvulnerable()
{
    return m_bInvulnerable;
}

void PlatformerObject::setLives(int lives)
{
    m_lives = std::max(std::min(lives, m_maxLives), 0);
}

void PlatformerObject::changeLives(int lives)
{
    setLives(m_lives + lives);
}

int PlatformerObject::getLives()
{
    return m_lives;
}

void PlatformerObject::hit(int damage)
{
    if (isInvulnerable()) {
        return;
    }

    m_currentAttackState = ON_HIT;
    changeLives(-damage);
};

void PlatformerObject::attack(PlatformerObject* pTarget)
{
    pTarget->hit(1);
};
bool PlatformerObject::isAttack()
{
    return m_bAttack;
}

int PlatformerObject::getDamageRange()
{
    return m_damageRange;
}

bool PlatformerObject::isFlipped()
{
    return m_bFlipped;
}

void PlatformerObject::setCurrentState(objectMotion state)
{
    m_currentState = state;
}
