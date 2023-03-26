#include "PhysicObject.hpp"
#include <iostream>

PhysicObject::PhysicObject()
    : m_jumpHeight(0)
    , m_moveSpeed(0)
    , m_footContact(0)
    , m_bOnGround(false)
    , m_bCanMoveRight(true)
    , m_bCanMoveLeft(true)
    , m_bRunning(false)
{}

PhysicObject::~PhysicObject() {}

void PhysicObject::update()
{
    m_bOnGround = this->getFootContact() > 0;
    m_bRunning = false;
}

void PhysicObject::createBody(const int x, const int y, const int width, const int height)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PhysicWorld::pixelToMeter(b2Vec2(x + width * 0.5f, y + height * 0.5f));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = PhysicWorld::Instance()->getWorld()->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(
        PhysicWorld::pixelToMeter(width) / 2.0f,
        PhysicWorld::pixelToMeter(height) / 2.0f);

    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 1;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    PhysicWorld::Instance()->createPolygonSensor(
        m_pBody,
        b2Vec2(0, height * 0.5),
        width - 0.5,
        1,
        PhysicWorld::CAT_FOOT_SENSOR,
        PhysicWorld::MASK_FOOT_SENSOR);
}

void PhysicObject::changeFootContact(int n)
{
    m_footContact += n;
}

void PhysicObject::moveRight()
{
    if (this->canMoveRight() == false) {
        return;
    }

    if (this->isOnGround()) {
        m_bRunning = true;
    }

    float speedDifference = PhysicWorld::pixelToMeter(m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

void PhysicObject::moveLeft()
{
    if (this->canMoveLeft() == false) {
        return;
    }

    if (this->isOnGround()) {
        m_bRunning = true;
    }

    float speedDifference =
        PhysicWorld::pixelToMeter(-m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

void PhysicObject::jump()
{
    if (m_pBody->GetLinearVelocity().y != 0) {
        return;
    }

    /* T = (2h/g)^(1/2) */
    float timeToJumpPeak =
        sqrt(2 * PhysicWorld::pixelToMeter(m_jumpHeight) / PhysicWorld::GRAVITY.y);

    /* F = 1/2.m.v^2 */

    b2Vec2 impulse = 0.5 * m_pBody->GetMass() *
                     std::pow((PhysicWorld::pixelToMeter(m_jumpHeight) / timeToJumpPeak), 2) *
                     b2Vec2(0, -1);

    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

b2Body* PhysicObject::getBody() const
{
    return m_pBody;
}

b2Vec2 PhysicObject::getPosition() const
{
    return PhysicWorld::meterToPixel(m_pBody->GetPosition());
}

float PhysicObject::getAngle() const
{
    return PhysicWorld::degToRad(m_pBody->GetAngle());
}

int PhysicObject::getFootContact() const
{
    return m_footContact;
}

bool PhysicObject::isOnGround() const
{
    return m_bOnGround;
}

void PhysicObject::setMoveRight(bool bMoveRight)
{
    m_bCanMoveRight = bMoveRight;
}

void PhysicObject::setMoveLeft(bool bMoveLeft)
{
    m_bCanMoveLeft = bMoveLeft;
}

bool PhysicObject::isRunning() const
{
    return m_bRunning;
}

bool PhysicObject::canMoveRight() const
{
    return m_bCanMoveRight;
}

bool PhysicObject::canMoveLeft() const
{
    return m_bCanMoveLeft;
}
