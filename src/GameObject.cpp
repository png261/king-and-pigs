#include "GameObject.hpp"

#include "Camera.hpp"
#include "Game.hpp"

GameObject::GameObject()
    : m_position(0, 0)
    , m_width(0)
    , m_height(0)
    , m_textureHeight(0)
    , m_textureWidth(0)
    , m_bUpdating(false)
    , m_angle(0)
    , m_bExist(true)
    , m_bFlipped(false)
    , m_footContact(0)
{}

GameObject::~GameObject()
{
    m_pBody = nullptr;
}

void GameObject::load(const LoaderParams* const pParams)
{
    m_position = b2Vec2(pParams->x(), pParams->y());

    m_width = pParams->width();
    m_height = pParams->height();

    m_textureWidth = pParams->textureWidth();
    m_textureHeight = pParams->textureHeight();
    m_textureX = pParams->textureX();
    m_textureY = pParams->textureY();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = m_position;
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = Box2D::Instance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;

    dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    dynamicBox.SetAsBox((m_width - 0.5) / 2.0f, 0.3, b2Vec2(0, m_height / 2.0f), 0);
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
        m_position - Camera::Instance()->getPosition(),
        m_textureWidth,
        m_textureHeight,
        m_pBody->GetAngle() / M_PI * 180,
        m_bFlipped);
}

void GameObject::update()
{
    m_position = m_pBody->GetPosition() - b2Vec2(m_textureWidth / 2.0f, m_textureHeight / 2.0f) +
                 b2Vec2(m_textureX, m_textureY);
    m_currentState = m_footContact > 0 ? ON_GROUND : ON_FLY;
    m_animations[m_curAnimation]->update();
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
