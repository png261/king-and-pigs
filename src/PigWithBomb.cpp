#include "PigWithBomb.hpp"
#include "Bomb.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

PigWithBomb::PigWithBomb()
    : Pig()
    , m_bThrowing(false)
{
    m_bCanJump = false;
}

PigWithBomb::~PigWithBomb() {}

void PigWithBomb::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Pig::load(std::move(pParams));
    this->loadAnimation();
}
void PigWithBomb::loadAnimation()
{
    Pig::loadAnimation();

    m_animations[IDLE] = std::make_unique<Animation>("pigWithBomb idle", 26, 26, 10);
    m_animations[RUN] = std::make_unique<Animation>("pigWithBomb run", 26, 26, 6);
    m_animations[THROWING] = std::make_unique<Animation>("pigWithBomb throwing", 26, 26, 5);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void PigWithBomb::update()
{
    Pig::update();
    if (m_seeingCategory == PhysicWorld::CAT_PLAYER && m_nearestDistance <= 100) {
        this->throwBomb();
        this->becomeNormal();
    }
}

void PigWithBomb::throwBomb()
{
    std::unique_ptr<LoaderParams> pParams = std::make_unique<LoaderParams>(LoaderParams(
        this->getPosition().x - m_width / 2.0f,
        this->getPosition().y - m_height / 2.0f - 10,
        7,
        7));

    GameObject* bomb = Game::Instance()->getLevel()->spawnGameObject("Bomb", std::move(pParams));
    bomb->getBody()->ApplyForce(
        b2Vec2(m_direction * 50, -32),
        bomb->getBody()->GetWorldCenter(),
        true);
    dynamic_cast<Bomb*>(bomb)->turnOn();
}

void PigWithBomb::becomeNormal()
{
    this->disappear();
    std::unique_ptr<LoaderParams> pParams2 = std::make_unique<LoaderParams>(LoaderParams(
        this->getPosition().x - (20 * 0.5f),
        this->getPosition().y - (20 * 0.5f),
        20,
        20));
    GameObject* obj = Game::Instance()->getLevel()->spawnGameObject("Pig", std::move(pParams2));
}
