#include "PigWithBox.hpp"
#include "Box.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

PigWithBox::PigWithBox()
    : Pig()
    , m_bThrowing(false)
{
    m_bCanJump = false;
}

PigWithBox::~PigWithBox() {}

void PigWithBox::loadAnimation()
{
    Pig::loadAnimation();

    m_animations[Animation::IDLE] =
        std::make_unique<Animation>(Animation("pigWithBox idle", 26, 30, 9));
    m_animations[Animation::RUN] =
        std::make_unique<Animation>(Animation("pigWithBox run", 26, 30, 6));
    m_animations[Animation::THROWING] =
        std::make_unique<Animation>(Animation("pigWithBox throwing", 26, 30, 5));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void PigWithBox::update()
{
    Pig::update();
    if (m_seeingCategory == PhysicWorld::CAT_PLAYER && m_nearestDistance <= 100) {
        this->throwBox();
        this->becomeNormal();
    }
}

void PigWithBox::throwBox()
{
    std::unique_ptr<LoaderParams> pParams = std::make_unique<LoaderParams>(LoaderParams(
        this->getPosition().x - m_width / 2.0f,
        this->getPosition().y - m_height / 2.0f - 20,
        20,
        20));

    GameObject* box = Game::Instance()->getLevel()->spawnGameObject("Box", std::move(pParams));
    box->getBody()->ApplyForce(
        b2Vec2(m_direction * 100, -32),
        box->getBody()->GetWorldCenter(),
        true);
}

void PigWithBox::becomeNormal()
{
    this->disappear();
    std::unique_ptr<LoaderParams> pParams2 = std::make_unique<LoaderParams>(LoaderParams(
        this->getPosition().x - (20 * 0.5f),
        this->getPosition().y - (20 * 0.5f),
        20,
        20));
    GameObject* obj = Game::Instance()->getLevel()->spawnGameObject("Pig", std::move(pParams2));
}
