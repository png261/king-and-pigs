#include "Box2D.hpp"
#include <iostream>
#include "AttackableObject.hpp"
#include "ContactListener.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "DoorIn.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "Pig.hpp"
#include "Player.hpp"

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

bool Box2D::init()
{
    m_pWorld = new b2World(Box2D::GRAVITY);
    m_pWorld->SetContactListener(new ContactListener);

    m_timeStep = 1.0f / 60.f;
    m_velocityIterations = 10;
    m_positionIterations = 8;

    m_pDebugDraw = new DebugDraw(Game::Instance()->getWindow());
    m_pWorld->SetDebugDraw(m_pDebugDraw);
    m_bDebugEnable = false;

    return true;
}


int Box2D::meterToPixel(const float meter)
{
    return static_cast<int>(floor(meter * Box2D::PIXEL_PER_METER));
}

float Box2D::pixelToMeter(const float pixel)
{
    return static_cast<float>(pixel * Box2D::METER_PER_PIXEL);
}

b2Vec2 Box2D::meterToPixel(const b2Vec2 meter)
{
    return {meter.x * Box2D::PIXEL_PER_METER, meter.y * Box2D::PIXEL_PER_METER};
};

b2Vec2 Box2D::pixelToMeter(const b2Vec2 pixel)
{
    return {pixel.x * Box2D::METER_PER_PIXEL, pixel.y * Box2D::METER_PER_PIXEL};
};

float Box2D::radToDeg(const float rad)
{
    return rad * Box2D::DEG_PER_RAD;
};

float Box2D::degToRad(const float deg)
{
    return deg * Box2D::RAD_PER_DEG;
};

void Box2D::createCollisionObject(const int width, const int height, const b2Vec2 position)
{
    b2BodyDef body;
    body.position = Box2D::pixelToMeter(position + b2Vec2(width * 0.5, height * 0.5));
    body.type = b2_staticBody;
    b2Body* const groundBody = this->getWorld()->CreateBody(&body);

    float w = Box2D::pixelToMeter(width);
    float h = Box2D::pixelToMeter(height);

    b2FixtureDef fixture;

    b2ChainShape box;
    b2Vec2 vertices[4];
    vertices[0].Set(-w / 2, -h / 2);
    vertices[1].Set(w / 2, -h / 2);
    vertices[2].Set(w / 2, h / 2);
    vertices[3].Set(-w / 2, h / 2);
    box.CreateLoop(vertices, 4);

    fixture.shape = &box;
    fixture.friction = Box2D::GROUND_FRICTION;
    fixture.filter.categoryBits = Box2D::CAT_WALL;
    groundBody->CreateFixture(&fixture);
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
        enemyVisionListener(contact);
        DoorInBeginContact(contact);
    }
}

void Box2D::enemyVisionListener(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;
    bool isSeeing = (catA | catB) == (Box2D::CAT_PLAYER | Box2D::CAT_ENEMY_VISION_SENSOR);
    if (!isSeeing) {
        return;
    }
    if (catA == Box2D::CAT_ENEMY_VISION_SENSOR) {
        GameObject* const enemy = (GameObject*)(A->GetBody()->GetUserData().pointer);
        GameObject* const player = (GameObject*)(B->GetBody()->GetUserData().pointer);
        std::cout << player->getPosition().x << std::endl;
    }

    if (catB == Box2D::CAT_ENEMY_VISION_SENSOR) {
        GameObject* const player = (GameObject*)(A->GetBody()->GetUserData().pointer);
        Pig* const enemy = dynamic_cast<Pig*>((GameObject*)(B->GetBody()->GetUserData().pointer));
        enemy->setFollowPosition(player->getPosition());
    }
}

void Box2D::DoorInBeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catA = fixtureA->GetFilterData().categoryBits;
    uint16 catB = fixtureB->GetFilterData().categoryBits;
    bool isPlayerDoor = (catA | catB) == (Box2D::CAT_DOOR_IN | Box2D::CAT_PLAYER);
    if (!isPlayerDoor) {
        return;
    }
    DoorIn* door = nullptr;
    Player* player = nullptr;

    if (catA == Box2D::CAT_DOOR_IN) {
        door = dynamic_cast<DoorIn*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
        player = dynamic_cast<Player*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
    } else {
        door = dynamic_cast<DoorIn*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
        player = dynamic_cast<Player*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
    }

    if (player == nullptr || door == nullptr) {
        return;
    }

    if (player->isWantDoorIn()) {
        door->open();
        player->doorIn();
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
    } else {
        handleAttack(B, A);
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
    for (b2Body* body = m_pWorld->GetBodyList(); body; body = body->GetNext()) {
        m_pWorld->DestroyBody(body);
    }
    /* delete m_pWorld; */
    /* m_pWorld = nullptr; */
}
