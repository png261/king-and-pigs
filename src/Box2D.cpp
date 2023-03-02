#include "Box2D.hpp"
#include <iostream>
#include "AttackableObject.hpp"
#include "ContactListener.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "InputHandler.hpp"
#include "GameObject.hpp"

const int Box2D::PPM = 32.0f;
const b2Vec2 Box2D::GRAVITY = b2Vec2(0.0f, 9.8f * Box2D::PPM);

Box2D::Box2D() {}

Box2D* Box2D::Instance()
{
    static Box2D* const pInstance = new Box2D();
    return pInstance;
}

void Box2D::createWall(int size, b2Vec2 position)
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position = position;
    b2Body* const groundBody = Box2D::Instance()->getWorld()->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(size / 2.0f, size / 2.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.friction = 1;
    fixtureDef.filter.categoryBits = Box2D::CAT_WALL;
    groundBody->CreateFixture(&fixtureDef);
}

bool Box2D::init()
{
    m_pWorld = new b2World(Box2D::GRAVITY);
    m_pDebugDraw = new DebugDraw();
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    /* flags += b2Draw::e_jointBit; */
    /* flags += b2Draw::e_centerOfMassBit; */
    /* flags += b2Draw::e_aabbBit; */
    /* flags += b2Draw::e_pairBit; */
    m_pDebugDraw->SetFlags(flags);

    m_pWorld->SetContactListener(new ContactListener);
    m_pWorld->SetDebugDraw(m_pDebugDraw);
    m_bDebugEnable = true;

    m_timeStep = 1.0f / 60.f;
    m_velocityIterations = 10;
    m_positionIterations = 8;

    return true;
}

void Box2D::handleEvents()
{
    if (InputHandler::Instance()->isKeyDown(KEY_Q)) {
        Box2D::Instance()->toggleDebugDraw();
    };

    for (b2Contact* contact = getWorld()->GetContactList(); contact; contact = contact->GetNext()) {
        b2Fixture* const fixtureA = contact->GetFixtureA();
        b2Fixture* const fixtureB = contact->GetFixtureB();
        uint16 const catA = fixtureA->GetFilterData().categoryBits;
        uint16 const catB = fixtureB->GetFilterData().categoryBits;

        if (((catA | catB) == (Box2D::CAT_ATTACK_SENSOR | Box2D::CAT_ENEMY)) ||
            ((catA | catB) == (Box2D::CAT_ATTACK_SENSOR | Box2D::CAT_PLAYER))) {
            if (catA == Box2D::CAT_ATTACK_SENSOR) {
                AttackableObject* const A = dynamic_cast<AttackableObject*>(
                    (GameObject*)(fixtureA->GetBody()->GetUserData().pointer));
                DamageableObject* const B = dynamic_cast<DamageableObject*>(
                    (GameObject*)(fixtureB->GetBody()->GetUserData().pointer));

                if (A != nullptr && B != nullptr && A->isAttack()) {
                    const char* direction = (const char*)fixtureA->GetUserData().pointer;
                    if (A->isTurnRight() == (std::string(direction) == "right")) {
                        B->damage(A->getDamage());
                    }
                }

            } else if (catB == Box2D::CAT_ATTACK_SENSOR) {
                AttackableObject* const B = dynamic_cast<AttackableObject*>(
                    (GameObject*)(fixtureB->GetBody()->GetUserData().pointer));
                DamageableObject* const A = dynamic_cast<DamageableObject*>(
                    (GameObject*)(fixtureA->GetBody()->GetUserData().pointer));

                if (A != nullptr && B != nullptr && B->isAttack()) {
                    const char* direction = (const char*)fixtureB->GetUserData().pointer;
                    if (B->isTurnRight() == (std::string(direction) == "right")) {
                        A->damage(B->getDamage());
                    }
                }
            }
        }
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

DebugDraw* Box2D::getDebugDraw()
{
    return m_pDebugDraw;
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

// Class Contact Listener
