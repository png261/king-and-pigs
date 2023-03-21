#include "PhysicWorld.hpp"
#include "AttackableObject.hpp"
#include "ContactListener.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "DoorIn.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "Pig.hpp"
#include "Player.hpp"

const float PhysicWorld::PIXEL_PER_METER = 32.0f;
const float PhysicWorld::METER_PER_PIXEL = 1 / PIXEL_PER_METER;
const float PhysicWorld::RAD_PER_DEG = 180 / b2_pi;
const float PhysicWorld::DEG_PER_RAD = b2_pi / 180;
const float PhysicWorld::GROUND_FRICTION = 1;
const b2Vec2 PhysicWorld::GRAVITY = {0.0f, 9.8f};

PhysicWorld::PhysicWorld()
    : m_pWorld(nullptr)
{}

PhysicWorld* PhysicWorld::Instance()
{
    static PhysicWorld* const pInstance = new PhysicWorld();
    return pInstance;
}

bool PhysicWorld::init(Window* window)
{
    m_pWorld = new b2World(GRAVITY);
    m_contactListener = std::make_unique<ContactListener>(ContactListener());
    m_pDebugDraw = std::make_unique<DebugDraw>(DebugDraw(window));
    m_pWorld->SetContactListener(new ContactListener);
    m_pWorld->SetDebugDraw(m_pDebugDraw.get());

    m_timeStep = 1.0f / 60.f;
    m_velocityIterations = 10;
    m_positionIterations = 8;

    m_bDebugEnable = false;

    return true;
}


int PhysicWorld::meterToPixel(const float meter)
{
    return static_cast<int>(floor(meter * PIXEL_PER_METER));
}

float PhysicWorld::pixelToMeter(const float pixel)
{
    return static_cast<float>(pixel * METER_PER_PIXEL);
}

b2Vec2 PhysicWorld::meterToPixel(const b2Vec2 meter)
{
    return PIXEL_PER_METER * meter;
};

b2Vec2 PhysicWorld::pixelToMeter(const b2Vec2 pixel)
{
    return METER_PER_PIXEL * pixel;
};

float PhysicWorld::radToDeg(const float rad)
{
    return rad * DEG_PER_RAD;
};

float PhysicWorld::degToRad(const float deg)
{
    return deg * RAD_PER_DEG;
};

void PhysicWorld::createCollisionObject(
    const FilterCategory category,
    const int width,
    const int height,
    const b2Vec2 position)
{
    b2BodyDef body;
    body.position = pixelToMeter(position + b2Vec2(width * 0.5, height * 0.5));
    body.type = b2_staticBody;
    b2Body* const groundBody = this->getWorld()->CreateBody(&body);

    float w = pixelToMeter(width);
    float h = pixelToMeter(height);

    b2FixtureDef fixture;

    b2ChainShape box;
    b2Vec2 vertices[4];
    vertices[0].Set(-w / 2, -h / 2);
    vertices[1].Set(w / 2, -h / 2);
    vertices[2].Set(w / 2, h / 2);
    vertices[3].Set(-w / 2, h / 2);
    box.CreateLoop(vertices, 4);

    fixture.shape = &box;
    fixture.friction = GROUND_FRICTION;
    fixture.filter.categoryBits = category;
    groundBody->CreateFixture(&fixture);
}

void PhysicWorld::handleEvents()
{
    if (InputHandler::Instance()->isKeyDown(KEY_Q)) {
        this->toggleDebugDraw();
    };

    this->contactListener();
}

void PhysicWorld::contactListener()
{
    for (b2Contact* contact = getWorld()->GetContactList(); contact != nullptr;
         contact = contact->GetNext()) {
        AttackListener(contact);
        DoorInListener(contact);
    }
}

void PhysicWorld::DoorInListener(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uint16 catA = fixtureA->GetFilterData().categoryBits;
    uint16 catB = fixtureB->GetFilterData().categoryBits;

    bool isPlayerDoor = catA == CAT_DOOR_IN && catB == CAT_PLAYER;
    if (!isPlayerDoor) {
        return;
    }

    DoorIn* door = dynamic_cast<DoorIn*>((GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
    Player* player =
        dynamic_cast<Player*>((GameObject*)(fixtureB->GetBody()->GetUserData().pointer));

    if (player == nullptr || door == nullptr) {
        return;
    }

    if (player->isWantDoorIn()) {
        if (door->isOpened()) {
            Game::Instance()->nextLevel();
        } else {
            door->open();
            player->doorIn();
        }
    }
}

void PhysicWorld::AttackListener(b2Contact* contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;

    bool isAttack = ((catA | catB) == (CAT_ATTACK_SENSOR | CAT_ENEMY)) ||
                    ((catA | catB) == (CAT_ATTACK_SENSOR | CAT_PLAYER));

    if (!isAttack) {
        return;
    }

    if (catA == CAT_ATTACK_SENSOR) {
        handleAttack(A, B);
    } else {
        handleAttack(B, A);
    }
}

void PhysicWorld::handleAttack(b2Fixture* Attacker, b2Fixture* Defender)
{
    AttackableObject* const A =
        dynamic_cast<AttackableObject*>((GameObject*)(Attacker->GetBody()->GetUserData().pointer));
    DamageableObject* const B =
        dynamic_cast<DamageableObject*>((GameObject*)(Defender->GetBody()->GetUserData().pointer));

    if (A == nullptr || B == nullptr || A->isAttack() == false) {
        return;
    }

    const char* direction = (const char*)Attacker->GetUserData().pointer;
    B->damage(A->getDamage());
}

void PhysicWorld::update()
{
    getWorld()->Step(m_timeStep, m_velocityIterations, m_positionIterations);
}

void PhysicWorld::debugDraw()
{
    if (!m_bDebugEnable) {
        return;
    }
    getWorld()->DebugDraw();
}


b2World* PhysicWorld::getWorld()
{
    return m_pWorld;
}

void PhysicWorld::toggleDebugDraw()
{
    m_bDebugEnable = !m_bDebugEnable;
}

void PhysicWorld::clean()
{
    m_pWorld->SetContactListener(nullptr);
    m_contactListener.reset();

    for (b2Body* body = m_pWorld->GetBodyList(); body; body = body->GetNext()) {
        m_pWorld->DestroyBody(body);
    }

    m_contactListener = std::make_unique<ContactListener>(ContactListener());
    m_pWorld->SetContactListener(m_contactListener.get());
    /* delete m_pWorld; */
    /* m_pWorld = nullptr; */
}

b2Fixture* PhysicWorld::createPolygonSensor(
    b2Body* body,
    float x,
    float y,
    int width,
    int height,
    FilterCategory category,
    FilterMask mask)
{
    b2PolygonShape polygon;
    polygon.SetAsBox(
        PhysicWorld::pixelToMeter(width * 0.5),
        PhysicWorld::pixelToMeter(height * 0.5),
        PhysicWorld::pixelToMeter(b2Vec2(x, y)),
        0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = category;
    fixtureDef.filter.maskBits = mask;

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(pixelToMeter(width) / 2.0f, pixelToMeter(height) / 2.0f);
    return body->CreateFixture(&fixtureDef);
}
