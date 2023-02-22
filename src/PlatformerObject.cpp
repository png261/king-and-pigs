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
    , m_attackRange(0)
    , m_attackDamage(0)
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
    bodyDef.position.Set(m_position.x, m_position.y);
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = Box2D::Instance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;

    dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    dynamicBox.SetAsBox(m_width / 2.0f, 0.3, b2Vec2(0, m_height / 2.0f), 0);
    b2FixtureDef footSensorDef;
    footSensorDef.shape = &dynamicBox;
    footSensorDef.isSensor = true;
    footSensorDef.filter.categoryBits = Box2D::CAT_FOOT_SENSOR;
    footSensorDef.filter.maskBits = Box2D::MASK_FOOT_SENSOR;
    m_pFootSensor = m_pBody->CreateFixture(&footSensorDef);

    dynamicBox.SetAsBox(m_attackRange / 2.0f, m_attackRange / 2.0f, b2Vec2(m_width / 2.0f, 0), 0);
    b2FixtureDef attackSensorDef;
    attackSensorDef.shape = &dynamicBox;
    attackSensorDef.isSensor = true;
    m_pAttackSensor = m_pBody->CreateFixture(&attackSensorDef);
}

void PlatformerObject::draw()
{
    m_animations[m_curAnimation]->draw(
        m_position.x + m_textureX - TheCamera::Instance()->getPosition().x,
        m_position.y + m_textureY - TheCamera::Instance()->getPosition().y,
        m_textureWidth,
        m_textureHeight,
        m_pBody->GetAngle() / M_PI * 180,
        m_bFlipped);
}

void PlatformerObject::update()
{
    if (m_footContact > 0) {
        m_currentState = ON_GROUND;
    } else {
        m_currentState = ON_FLY;
    }

    m_position = m_pBody->GetPosition();
}

std::string PlatformerObject::type() const
{
    return "GameObject";
}

bool PlatformerObject::isInvulnerable() const
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

int PlatformerObject::getLives() const
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
    pTarget->hit(getAttackDamage());
};

bool PlatformerObject::isAttack() const
{
    return m_bAttack;
}

int PlatformerObject::getAttackRange() const
{
    return m_attackRange;
}

int PlatformerObject::getAttackDamage() const
{
    return m_attackDamage;
}

bool PlatformerObject::isFlipped() const
{
    return m_bFlipped;
}

void PlatformerObject::setCurrentState(objectMotion state)
{
    m_currentState = state;
}
