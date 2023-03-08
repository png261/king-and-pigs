#include "GameObject.hpp"

#include "Box2D.hpp"
#include "Camera.hpp"
#include "Game.hpp"

GameObject::GameObject()
    : m_width(0)
    , m_height(0)
    , m_bUpdating(false)
    , m_angle(0)
    , m_bExist(true)
    , m_bFlipped(false)
    , m_footContact(0)
    , m_moveSpeed(0)
    , m_jumpHeight(0)
{}

GameObject::~GameObject()
{
    m_pBody = nullptr;
}

void GameObject::load(const LoaderParams* const pParams)
{
    m_width = pParams->width();
    m_height = pParams->height();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Box2D::pixelToMeter(b2Vec2(pParams->x(), pParams->y()));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = Box2D::Instance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;

    dynamicBox.SetAsBox(Box2D::pixelToMeter(m_width) / 2.0f, Box2D::pixelToMeter(m_height) / 2.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    dynamicBox.SetAsBox(
        (Box2D::pixelToMeter(m_width - 0.5)) / 2.0f,
        Box2D::pixelToMeter(0.5),
        b2Vec2(0, Box2D::pixelToMeter(m_height) / 2.0f),
        0);
    b2FixtureDef footSensorDef;
    footSensorDef.shape = &dynamicBox;
    footSensorDef.isSensor = true;
    footSensorDef.filter.categoryBits = Box2D::CAT_FOOT_SENSOR;
    footSensorDef.filter.maskBits = Box2D::MASK_FOOT_SENSOR;
    m_pFootSensor = m_pBody->CreateFixture(&footSensorDef);
}

void GameObject::draw()
{
    m_animations[m_curAnimation]->draw(
        this->getPosition() - Camera::Instance()->getPosition(),
        this->getAngle(),
        m_bFlipped);
}

void GameObject::update()
{
    m_currentState = m_footContact > 0 ? ON_GROUND : ON_FLY;
    m_animations[m_curAnimation]->update();
}

b2Vec2 GameObject::getPosition()
{
    return Box2D::meterToPixel(m_pBody->GetPosition());
}

float GameObject::getAngle()
{
    return Box2D::meterToPixel(m_pBody->GetAngle());
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

void GameObject::setUpdating(const bool bUpdating)
{
    m_bUpdating = bUpdating;
}

bool GameObject::isExist() const
{
    return m_bExist;
}

void GameObject::changeFootContact(int n)
{
    m_footContact += n;
}


void GameObject::moveRight()
{
    float speedDifference = Box2D::pixelToMeter(m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);

    m_bFlipped = false;
}

void GameObject::moveLeft()
{
    float speedDifference = -Box2D::pixelToMeter(m_moveSpeed) - m_pBody->GetLinearVelocity().x;
    b2Vec2 impulse{m_pBody->GetMass() * speedDifference, 0};
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);

    m_bFlipped = true;
}

void GameObject::jump()
{
    float timeToJumpPeak = sqrt(2 * Box2D::pixelToMeter(m_jumpHeight) / Box2D::GRAVITY.y);
    b2Vec2 impulse =
        -b2Vec2(0, m_pBody->GetMass() * Box2D::pixelToMeter(m_jumpHeight) / timeToJumpPeak);
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}
