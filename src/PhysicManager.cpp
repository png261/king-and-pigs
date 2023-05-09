#include "PhysicManager.hpp"

#include "AttackerObject.hpp"
#include "CONSTANT.hpp"
#include "ContactListener.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "DoorExit.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Pig.hpp"
#include "Player.hpp"
#include "Utils.hpp"

PhysicManager::PhysicManager()
    : time_step_(1.0f / 60.f)
    , velocity_iterations_(10)
    , position_iterations_(8)
{}

PhysicManager& PhysicManager::Instance()
{
    static PhysicManager instance{};
    return instance;
}

void PhysicManager::init(Window* const window)
{
    world_ = std::make_unique<b2World>(b2Vec2(0, GRAVITY));
    debugDraw_ = std::make_unique<DebugDraw>(window);
    world_->SetDebugDraw(debugDraw_.get());
    createContactListener();
}

void PhysicManager::update()
{
    getWorld()->Step(time_step_, velocity_iterations_, position_iterations_);
    contactListener_->realTimeListener(getWorld()->GetContactList());
}

void PhysicManager::clean()
{
    world_->SetContactListener(nullptr);
    contactListener_.reset();
    for (b2Body* body = world_->GetBodyList(); body; body = body->GetNext()) {
        world_->DestroyBody(body);
    }
}

void PhysicManager::debugDraw() const
{
    getWorld()->DebugDraw();
}

b2World* PhysicManager::getWorld() const
{
    return world_.get();
}

void PhysicManager::createContactListener()
{
    contactListener_ = std::make_unique<ContactListener>(ContactListener());
    world_->SetContactListener(contactListener_.get());
}

b2Body* PhysicManager::createStaticBody(
    const b2Vec2& position,
    const int width,
    const int height,
    const ContactCategory category,
    const ContactMask mask) const
{
    b2BodyDef bodyDef;
    bodyDef.position = Utils::pixelToMeter(position + b2Vec2(width * 0.5, height * 0.5));
    bodyDef.type = b2_staticBody;
    b2Body* const body = getWorld()->CreateBody(&bodyDef);

    float w = Utils::pixelToMeter(width);
    float h = Utils::pixelToMeter(height);

    b2ChainShape box;
    b2Vec2 vertices[4];
    vertices[0].Set(-w * 0.5f, -h * 0.5f);
    vertices[1].Set(w * 0.5f, -h * 0.5f);
    vertices[2].Set(w * 0.5f, h * 0.5f);
    vertices[3].Set(-w * 0.5f, h * 0.5f);
    box.CreateLoop(vertices, 4);

    b2FixtureDef fixture;
    fixture.shape = &box;
    fixture.friction = GROUND_FRICTION;
    fixture.filter.categoryBits = category;
    fixture.filter.maskBits = mask;
    body->CreateFixture(&fixture);

    return body;
}

b2Fixture* PhysicManager::createCircleBody(
    b2Body*& body,
    const b2Vec2& position,
    const int radius,
    const ContactCategory category,
    const ContactMask mask) const
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Utils::pixelToMeter(b2Vec2(position) + 0.5 * b2Vec2(radius, radius));
    bodyDef.fixedRotation = true;
    body = getWorld()->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = Utils::pixelToMeter(radius);

    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 1;
    fixture.friction = 0.3;
    fixture.filter.categoryBits = category;
    fixture.filter.maskBits = mask;

    return body->CreateFixture(&fixture);
}
