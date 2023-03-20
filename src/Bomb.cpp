#include "Bomb.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"

Bomb::Bomb()
    : GameObject()
    , AttackableObject(1, 50, 9999)
    , m_bOn(false)
{}

Bomb::~Bomb() {}

void Bomb::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_BOMB;
    filter.maskBits = PhysicWorld::MASK_BOMB;
    m_pFixture->SetFilterData(filter);

    this->createAttackSensor(getBody(), m_width, PhysicWorld::MASK_ENEMY_ATTACK_SENSOR);
    this->loadAnimation();
    onTimer.setTime(1000);
}

void Bomb::loadAnimation()
{
    m_animations[Animation::BOMB_OFF] = std::make_unique<Animation>(Animation("bomb off", 52, 56));
    m_animations[Animation::BOMB_ON] = std::make_unique<Animation>(Animation("bomb on", 52, 56, 4));
    m_animations[Animation::BOMB_EXPLODE] =
        std::make_unique<Animation>(Animation("bomb explode", 52, 56, 6, false));

    m_curAnimation = Animation::BOMB_OFF;
    m_animations[m_curAnimation]->start();
}

void Bomb::update()
{
    if (this->isOn() && m_curAnimation == Animation::BOMB_EXPLODE &&
        m_animations[m_curAnimation]->isFinished()) {
        this->disappear();
        return;
    }

    GameObject::update();
    AttackableObject::update();

    if (this->isOn() && onTimer.isDone()) {
        this->explode();
    }

    this->updateAnimaton();
}

void Bomb::turnOn()
{
    m_bOn = true;
    onTimer.start();
    m_curAnimation = Animation::BOMB_ON;
    m_animations[m_curAnimation]->start();
}

void Bomb::explode()
{
    this->attack();
}


void Bomb::updateAnimaton()
{
    if (this->isAttack()) {
        m_curAnimation = Animation::BOMB_EXPLODE;
        m_animations[m_curAnimation]->start();
    }
}

bool Bomb::isOn() const
{
    return m_bOn;
}
