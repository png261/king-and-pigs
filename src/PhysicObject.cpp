#include "PhysicObject.hpp"

PhysicObject::PhysicObject()
    : m_jumpHeight(0)
    , m_moveSpeed(0)
    , m_footContact(0)
    , m_bOnGround(false)
{}

PhysicObject::~PhysicObject() {}

void PhysicObject::update()
{
    m_bOnGround = this->getFootContact() > 0;
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
    fixtureDef.friction = 0.3;
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
    float speedDifference = PhysicWorld::pixelToMeter(m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

void PhysicObject::moveLeft()
{
    float speedDifference =
        -PhysicWorld::pixelToMeter(m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

void PhysicObject::jump()
{
    float timeToJumpPeak =
        sqrt(2 * PhysicWorld::pixelToMeter(m_jumpHeight) / PhysicWorld::GRAVITY.y);
    b2Vec2 impulse =
        -b2Vec2(0, m_pBody->GetMass() * PhysicWorld::pixelToMeter(m_jumpHeight) / timeToJumpPeak);
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
    return PhysicWorld::meterToPixel(m_pBody->GetAngle());
}

int PhysicObject::getFootContact() const
{
    return m_footContact;
}

bool PhysicObject::isOnGround() const
{
    return m_bOnGround;
}
