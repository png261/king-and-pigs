#include "Box2D.hpp"
#include "ContactListener.hpp"
#include "DebugDraw.hpp"

const int Box2D::PPM = 32.0f;
const b2Vec2 Box2D::GRAVITY = b2Vec2(0.0f, 9.8f * Box2D::PPM);

Box2D* Box2D::Instance()
{
    static Box2D* pInstance = new Box2D();
    return pInstance;
}

b2World* Box2D::init()
{
    m_pWorld = new b2World(Box2D::GRAVITY);
    m_pWorld->SetContactListener(new ContactListener);
    m_pDebugDraw = new DebugDraw();
    m_pWorld->SetDebugDraw(m_pDebugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    /* flags += b2Draw::e_jointBit; */
    /* flags += b2Draw::e_centerOfMassBit; */
    /* flags += b2Draw::e_aabbBit; */
    /* flags += b2Draw::e_pairBit; */
    m_pDebugDraw->SetFlags(flags);
    m_bDebugEnable = true;
    return m_pWorld;
}

void Box2D::update()
{
    float timeStep = 1.0f / 60.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    getWorld()->Step(timeStep, velocityIterations, positionIterations);
}

void Box2D::debugDraw()
{
    if (m_bDebugEnable) {
        getWorld()->DebugDraw();
    }
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
