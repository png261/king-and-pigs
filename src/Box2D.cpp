#include "Box2D.hpp"
#include <iostream>
#include "AttackableObject.hpp"
#include "ContactListener.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"

const float Box2D::PIXEL_PER_METER = 32.0f;
const float Box2D::METER_PER_PIXEL = 1 / PIXEL_PER_METER;
const float Box2D::RAD_PER_DEG = 180 / b2_pi;
const float Box2D::DEG_PER_RAD = b2_pi / 180;
const float Box2D::GROUND_FRICTION = 1;
const b2Vec2 Box2D::GRAVITY = {0.0f, 9.8f};

Box2D::Box2D() {}

Box2D* Box2D::Instance()
{
    static Box2D* const pInstance = new Box2D();
    return pInstance;
}

int Box2D::meterToPixel(float meter)
{
    return static_cast<int>(floor(meter * Box2D::PIXEL_PER_METER));
}

float Box2D::pixelToMeter(float pixel)
{
    return static_cast<float>(pixel * Box2D::METER_PER_PIXEL);
}

b2Vec2 Box2D::meterToPixel(b2Vec2 meter)
{
    return {meter.x * Box2D::PIXEL_PER_METER, meter.y * Box2D::PIXEL_PER_METER};
};

b2Vec2 Box2D::pixelToMeter(b2Vec2 pixel)
{
    return {pixel.x * Box2D::METER_PER_PIXEL, pixel.y * Box2D::METER_PER_PIXEL};
};

float Box2D::radToDeg(float rad)
{
    return rad * Box2D::DEG_PER_RAD;
};

float Box2D::degToRad(float deg)
{
    return deg * Box2D::RAD_PER_DEG;
};

void Box2D::createWall(int size, b2Vec2 position)
{
    b2BodyDef body;
    body.position = Box2D::pixelToMeter(position);
    body.type = b2_staticBody;
    b2Body* const groundBody = this->getWorld()->CreateBody(&body);

    float width = Box2D::pixelToMeter(size);
    float height = Box2D::pixelToMeter(size);

    b2FixtureDef fixture;

    b2ChainShape box;
    b2Vec2 vertices[4];
    vertices[0].Set(-width / 2, -height / 2);
    vertices[1].Set(width / 2, -height / 2);
    vertices[2].Set(width / 2, height / 2);
    vertices[3].Set(-width / 2, height / 2);
    box.CreateLoop(vertices, 4);

    fixture.shape = &box;
    fixture.friction = Box2D::GROUND_FRICTION;
    fixture.filter.categoryBits = Box2D::CAT_WALL;
    groundBody->CreateFixture(&fixture);
}

bool Box2D::init()
{
    m_pWorld = new b2World(Box2D::GRAVITY);
    m_pWorld->SetContactListener(new ContactListener);

    m_timeStep = 1.0f / 60.f;
    m_velocityIterations = 10;
    m_positionIterations = 8;

    m_pDebugDraw = new DebugDraw();
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    /* flags += b2Draw::e_jointBit; */
    /* flags += b2Draw::e_centerOfMassBit; */
    /* flags += b2Draw::e_aabbBit; */
    /* flags += b2Draw::e_pairBit; */
    m_pDebugDraw->SetFlags(flags);
    m_pWorld->SetDebugDraw(m_pDebugDraw);
    m_bDebugEnable = true;

    return true;
}

void Box2D::handleEvents()
{
    if (InputHandler::Instance()->isKeyDown(KEY_Q)) {
        this->toggleDebugDraw();
    };

    this->contactListener();
}

void Box2D::contactListener()
{
    for (b2Contact* contact = getWorld()->GetContactList(); contact != nullptr;
         contact = contact->GetNext()) {
        attackListener(contact);
    }
}

void Box2D::attackListener(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;
    bool isAttack = ((catA | catB) == (Box2D::CAT_ATTACK_SENSOR | Box2D::CAT_ENEMY)) ||
                    ((catA | catB) == (Box2D::CAT_ATTACK_SENSOR | Box2D::CAT_PLAYER));

    if (!isAttack) {
        return;
    }

    if (catA == Box2D::CAT_ATTACK_SENSOR) {
        handleAttack(A, B);
        return;
    }

    if (catB == Box2D::CAT_ATTACK_SENSOR) {
        handleAttack(B, A);
        return;
    }
}

void Box2D::handleAttack(b2Fixture* Attacker, b2Fixture* Defender)
{
    AttackableObject* const A =
        dynamic_cast<AttackableObject*>((GameObject*)(Attacker->GetBody()->GetUserData().pointer));
    DamageableObject* const B =
        dynamic_cast<DamageableObject*>((GameObject*)(Defender->GetBody()->GetUserData().pointer));

    if (A == nullptr || B == nullptr || A->isAttack() == false) {
        return;
    }

    const char* direction = (const char*)Attacker->GetUserData().pointer;
    if (A->isTurnRight() == (std::string(direction) == "right")) {
        B->damage(A->getDamage());
    }
}

void Box2D::update()
{
    getWorld()->Step(m_timeStep, m_velocityIterations, m_positionIterations);
}

void Box2D::debugDraw()
{
    if (!m_bDebugEnable) {
        return;
    }
    getWorld()->DebugDraw();
}


b2World* Box2D::getWorld()
{
    return m_pWorld;
}

void Box2D::toggleDebugDraw()
{
    m_bDebugEnable = !m_bDebugEnable;
}

void Box2D::clean()
{
    delete m_pWorld;
    m_pWorld = nullptr;
}
