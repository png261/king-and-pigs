#include "Bomb.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "SoundManager.hpp"

Bomb::Bomb()
    : GameObject()
    , AttackerObject(1, 20, 9999)
    , m_bOn(false)
{}

void Bomb::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PhysicWorld::pixelToMeter(
        b2Vec2(pParams->x(), pParams->y()) + 0.5f * b2Vec2(m_width, m_height));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_pBody = PhysicWorld::Instance().getWorld()->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = PhysicWorld::pixelToMeter(m_width);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = PhysicWorld::CAT_BOMB;
    fixtureDef.filter.maskBits = PhysicWorld::MASK_BOMB;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    createCircleSensor(
        {0, 0},
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    loadAnimation();
    onTimer.setTime(1000);
}

void Bomb::loadAnimation()
{
    m_animations[OFF] = std::make_unique<Animation>("bomb off", 52, 56);
    m_animations[ON] = std::make_unique<Animation>("bomb on", 52, 56, 4);
    m_animations[EXPLODE] = std::make_unique<Animation>("bomb explode", 52, 56, 6, false);

    m_curAnimation = OFF;
    m_animations[m_curAnimation]->start();
}

void Bomb::update()
{
    if (isOn() && m_curAnimation == EXPLODE && m_animations[m_curAnimation]->isFinished()) {
        disappear();
        return;
    }

    GameObject::update();
    AttackerObject::update();

    if (isOn() && onTimer.isDone()) {
        explode();
    }

    updateAnimaton();
}

void Bomb::turnOn()
{
    SoundManager::Instance().playSFX("bomb on");
    m_bOn = true;
    onTimer.start();
    m_curAnimation = ON;
    m_animations[m_curAnimation]->start();
}

void Bomb::explode()
{
    SoundManager::Instance().playSFX("bomb explode");
    attack();
}


void Bomb::updateAnimaton()
{
    if (isAttack()) {
        m_curAnimation = EXPLODE;
        m_animations[m_curAnimation]->start();
    }
}

bool Bomb::isOn() const
{
    return m_bOn;
}
