#include "PhysicWorld.hpp"
#include "AttackerObject.hpp"
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
const float PhysicWorld::GROUND_FRICTION = 5;
const b2Vec2 PhysicWorld::GRAVITY = {0.0f, 10.0f};

PhysicWorld::PhysicWorld() {}

PhysicWorld& PhysicWorld::Instance()
{
    static PhysicWorld s_instance{};
    return s_instance;
}

bool PhysicWorld::init(std::shared_ptr<Window> const& window)
{
    m_pWorld = new b2World(GRAVITY);
    m_contactListener = std::make_unique<ContactListener>(ContactListener());
    m_pDebugDraw = std::make_unique<DebugDraw>(DebugDraw(window));
    m_pWorld->SetContactListener(new ContactListener);
    m_pWorld->SetDebugDraw(m_pDebugDraw.get());

    m_timeStep = 1.0f / 60.f;
    m_velocityIterations = 10;
    m_positionIterations = 8;
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

b2Body* PhysicWorld::createStaticBody(
    const b2Vec2 position,
    const int width,
    const int height,
    const Category category,
    const Mask mask)
{
    b2BodyDef bodyDef;
    bodyDef.position = pixelToMeter(position + b2Vec2(width * 0.5, height * 0.5));
    bodyDef.type = b2_staticBody;
    b2Body* const body = getWorld()->CreateBody(&bodyDef);

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
    fixture.filter.maskBits = mask;
    body->CreateFixture(&fixture);
    return body;
}

void PhysicWorld::DoorInListener(b2Contact* const contact)
{
    b2Fixture* const fixtureA = contact->GetFixtureA();
    b2Fixture* const fixtureB = contact->GetFixtureB();
    const uint16 catA = fixtureA->GetFilterData().categoryBits;
    const uint16 catB = fixtureB->GetFilterData().categoryBits;

    if (catA != CAT_DOOR_IN || catB != CAT_PLAYER) {
        return;
    }

    DoorIn* const door = (DoorIn*)(fixtureA->GetBody()->GetUserData().pointer);
    Player* const player = (Player*)(fixtureB->GetBody()->GetUserData().pointer);

    if (player == nullptr || door == nullptr) {
        return;
    }

    if (!player->isWantDoorIn()) {
        return;
    }

    if (door->isOpened()) {
        Game::Instance().nextLevel();
        return;
    }

    player->doorIn();
    door->open();
}

void PhysicWorld::AttackListener(b2Contact* const contact)
{
    b2Fixture* const A = contact->GetFixtureA();
    b2Fixture* const B = contact->GetFixtureB();
    uint16 const catA = A->GetFilterData().categoryBits;
    uint16 const catB = B->GetFilterData().categoryBits;

    if (catB == CAT_ATTACK_SENSOR && catA & (CAT_PIG | CAT_PLAYER | CAT_BOX)) {
        handleAttack(B, A);
    }
}

void PhysicWorld::handleAttack(b2Fixture* const Attacker, b2Fixture* const Defender)
{
    AttackerObject* const A =
        dynamic_cast<AttackerObject*>((GameObject*)(Attacker->GetBody()->GetUserData().pointer));
    DamageableObject* const B =
        dynamic_cast<DamageableObject*>((GameObject*)(Defender->GetBody()->GetUserData().pointer));

    if (A == nullptr || B == nullptr || !A->isDaming()) {
        return;
    }

    const char* direction = (const char*)Attacker->GetUserData().pointer;
    B->damage(A->getDamage());
}

void PhysicWorld::update()
{
    getWorld()->Step(m_timeStep, m_velocityIterations, m_positionIterations);

    for (b2Contact* contact = getWorld()->GetContactList(); contact != nullptr;
         contact = contact->GetNext()) {
        AttackListener(contact);
        DoorInListener(contact);
    }
}

void PhysicWorld::debugDraw()
{
    getWorld()->DebugDraw();
}


b2World* PhysicWorld::getWorld()
{
    return m_pWorld;
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
}
