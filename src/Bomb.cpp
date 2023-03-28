#include "Bomb.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"

Bomb::Bomb()
    : GameObject()
    , AttackerObject(1, 20, 9999)
    , m_bOn(false)
{}

Bomb::~Bomb() {}

void Bomb::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PhysicWorld::pixelToMeter(
        b2Vec2(pParams->x(), pParams->y()) + 0.5 * b2Vec2(m_width, m_height));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = PhysicWorld::Instance()->getWorld()->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = PhysicWorld::pixelToMeter(m_width);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.filter.categoryBits = PhysicWorld::CAT_BOMB;
    fixtureDef.filter.maskBits = PhysicWorld::MASK_BOMB;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    PhysicWorld::Instance()->createCircleSensor(
        m_pBody,
        {0, 0},
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    this->loadAnimation();
    onTimer.setTime(1000);
}

void Bomb::loadAnimation()
{
    m_animations[OFF] = new Animation("bomb off", 52, 56);
    m_animations[ON] = new Animation("bomb on", 52, 56, 4);
    m_animations[EXPLODE] =
        new Animation("bomb explode", 52, 56, 6, false);

    m_curAnimation = OFF;
    m_animations[m_curAnimation]->start();
}

void Bomb::update()
{
    if (this->isOn() && m_curAnimation == EXPLODE && m_animations[m_curAnimation]->isFinished()) {
        this->disappear();
        return;
    }

    GameObject::update();
    AttackerObject::update();

    if (this->isOn() && onTimer.isDone()) {
        this->explode();
    }

    this->updateAnimaton();
}

void Bomb::turnOn()
{
    m_bOn = true;
    onTimer.start();
    m_curAnimation = ON;
    m_animations[m_curAnimation]->start();
}

void Bomb::explode()
{
    this->attack();
}


void Bomb::updateAnimaton()
{
    if (this->isAttack()) {
        m_curAnimation = EXPLODE;
        m_animations[m_curAnimation]->start();
    }
}

bool Bomb::isOn() const
{
    return m_bOn;
}
