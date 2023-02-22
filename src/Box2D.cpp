#include "Box2D.hpp"
#include <iostream>
#include "ContactListener.hpp"
#include "DebugDraw.hpp"
#include "InputHandler.hpp"
#include "PlatformerObject.hpp"

const int Box2D::PPM = 32.0f;
const b2Vec2 Box2D::GRAVITY = b2Vec2(0.0f, 9.8f * Box2D::PPM);

Box2D::Box2D() {}

Box2D* Box2D::Instance()
{
    static Box2D* pInstance = new Box2D();
    return pInstance;
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
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Q)) {
        Box2D::Instance()->toggleDebugDraw();
    };

    for (b2Contact* contact = getWorld()->GetContactList(); contact; contact = contact->GetNext()) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        uint16 catA = fixtureA->GetFilterData().categoryBits;
        uint16 catB = fixtureB->GetFilterData().categoryBits;

        if (((catA | catB) == (Box2D::CAT_ATTACK_SENSOR | Box2D::CAT_ENEMY)) ||
            ((catA | catB) == (Box2D::CAT_ATTACK_SENSOR | Box2D::CAT_PLAYER))) {
            PlatformerObject* A = (PlatformerObject*)(fixtureA->GetBody()->GetUserData().pointer);
            PlatformerObject* B = (PlatformerObject*)(fixtureB->GetBody()->GetUserData().pointer);
            if (A == nullptr || B == nullptr) {
                continue;
            }

            if (catA == Box2D::CAT_ATTACK_SENSOR && A->isAttack()) {
                A->attack(B);
            } else if (catB == Box2D::CAT_ATTACK_SENSOR && B->isAttack()) {
                B->attack(A);
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

// Class Contact Listener
