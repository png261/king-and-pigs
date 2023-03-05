#include "Box2D.hpp"
#include "AttackableObject.hpp"
#include "ContactListener.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"

const int Box2D::PPM = 32.0f;
const b2Vec2 Box2D::GRAVITY = b2Vec2(0.0f, 9.8f * Box2D::PPM);

Box2D::Box2D() {}

Box2D* Box2D::Instance()
{
    static Box2D* const pInstance = new Box2D();
    return pInstance;
}

int Box2D::metterToPixel(int metter)
{
    return metter * Box2D::PPM;
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
    fixtureDef.friction = 5;
    fixtureDef.filter.categoryBits = Box2D::CAT_WALL;
    groundBody->CreateFixture(&fixtureDef);
}

bool Box2D::init()
{
    m_pWorld = new b2World(Box2D::GRAVITY);
    m_pDebugDraw = new DebugDraw();
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
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
        this->toggleDebugDraw();
    };

    this->contactListener();
}

void Box2D::contactListener()
{
    for (b2Contact* contact = getWorld()->GetContactList(); contact; contact = contact->GetNext()) {
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
