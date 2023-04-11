#include "PhysicObject.hpp"
#include <iostream>
#include "Log.hpp"

PhysicObject::PhysicObject()
    : m_jumpHeight(0)
    , m_moveSpeed(0)
    , m_footContact(0)
    , m_bOnGround(false)
    , m_bCanMoveRight(true)
    , m_bCanMoveLeft(true)
    , m_bRunning(false)
    , m_bCanJump(true)
    , m_bDisableJump(false)
{}

void PhysicObject::update()
{
    m_bOnGround = getFootContact() > 0;
    m_bCanJump = getBody()->GetLinearVelocity().y >= 0;
    m_bRunning = false;
}

void PhysicObject::createBody(const int x, const int y, const int width, const int height)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PhysicWorld::pixelToMeter(b2Vec2(x + width * 0.5f, y + height * 0.5f));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = PhysicWorld::Instance().getWorld()->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(
        PhysicWorld::pixelToMeter(width) / 2.0f,
        PhysicWorld::pixelToMeter(height) / 2.0f);

    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 1;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    createPolygonSensor(
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
    if (!canMoveRight()) {
        return;
    }

    if (isOnGround()) {
        m_bRunning = true;
    }

    float speedDifference = PhysicWorld::pixelToMeter(m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

void PhysicObject::moveLeft()
{
    if (!canMoveLeft()) {
        return;
    }

    if (isOnGround()) {
        m_bRunning = true;
    }

    float speedDifference =
        PhysicWorld::pixelToMeter(-m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}

void PhysicObject::jump()
{
    if (m_bDisableJump) {
        return;
    }

    if (!canJump()) {
        return;
    }

    if (!isOnGround()) {
        return;
    }

    float timeToJumpPeak =
        sqrt(2 * PhysicWorld::pixelToMeter(m_jumpHeight) / PhysicWorld::GRAVITY.y);

    float velocity = PhysicWorld::pixelToMeter(m_jumpHeight) / timeToJumpPeak;
    b2Vec2 impulse = m_pBody->GetMass() * std::pow(velocity, 2) * b2Vec2(0, -1);

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

bool PhysicObject::canJump() const
{
    return m_bCanJump;
}

bool PhysicObject::isDisableJump() const
{
    return m_bDisableJump;
}

void PhysicObject::setFilterData(PhysicWorld::Category category, PhysicWorld::Mask mask)
{
    if (m_pFixture == nullptr) {
        return;
    }

    b2Filter filter;
    filter.categoryBits = category;
    filter.maskBits = mask;
    m_pFixture->SetFilterData(filter);
}

b2Fixture* PhysicObject::createPolygonSensor(
    b2Vec2 position,
    int width,
    int height,
    PhysicWorld::Category category,
    PhysicWorld::Mask mask)
{
    b2PolygonShape polygon;
    polygon.SetAsBox(
        PhysicWorld::pixelToMeter(width * 0.5),
        PhysicWorld::pixelToMeter(height * 0.5),
        PhysicWorld::pixelToMeter(position),
        0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = category;
    fixtureDef.filter.maskBits = mask;
    return getBody()->CreateFixture(&fixtureDef);
}

b2Fixture* PhysicObject::createCircleSensor(
    const b2Vec2 position,
    const int radius,
    const PhysicWorld::Category category,
    const PhysicWorld::Mask mask)
{
    b2CircleShape circle;
    circle.m_p = PhysicWorld::pixelToMeter(position);
    circle.m_radius = PhysicWorld::pixelToMeter(radius);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = category;
    fixtureDef.filter.maskBits = mask;

    return getBody()->CreateFixture(&fixtureDef);
}

b2Fixture* PhysicObject::createCircleBody(
    b2Body*& body,
    const b2Vec2 position,
    const int radius,
    const PhysicWorld::Category category,
    const PhysicWorld::Mask mask)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PhysicWorld::pixelToMeter(b2Vec2(position) + 0.5 * b2Vec2(radius, radius));
    bodyDef.fixedRotation = true;
    body = PhysicWorld::Instance().getWorld()->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = PhysicWorld::pixelToMeter(radius);

    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 1;
    fixture.friction = 0.3;
    fixture.filter.categoryBits = category;
    fixture.filter.maskBits = mask;

    return body->CreateFixture(&fixture);
}
