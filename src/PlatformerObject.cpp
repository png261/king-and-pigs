#include "PlatformerObject.hpp"

#include "Box2D.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

PlatformerObject::PlatformerObject()
    : GameObject()
    , m_footContact(0)
    , m_direction(DIRECTION_RIGHT)

{}

void PlatformerObject::load(const LoaderParams* pParams)
{
    GameObject::load(pParams);

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

    dynamicBox.SetAsBox(m_width / 2.0f, 0.3, b2Vec2(0, m_height / 2.0f), 0);
    b2FixtureDef footSensorDef;
    footSensorDef.shape = &dynamicBox;
    footSensorDef.isSensor = true;
    footSensorDef.filter.categoryBits = Box2D::CAT_FOOT_SENSOR;
    footSensorDef.filter.maskBits = Box2D::MASK_FOOT_SENSOR;
    m_pFootSensor = m_pBody->CreateFixture(&footSensorDef);
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
    m_position = m_pBody->GetPosition();
    m_currentState = m_footContact > 0 ? ON_GROUND : ON_FLY;
}

std::string PlatformerObject::type() const
{
    return "GameObject";
}

PlatformerObject::direction PlatformerObject::getDirection() const
{
    return m_direction;
}

bool PlatformerObject::isFlipped() const
{
    return m_bFlipped;
}
