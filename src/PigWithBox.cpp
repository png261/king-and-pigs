#include "PigWithBox.hpp"
#include "Box.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

PigWithBox::PigWithBox()
    : Pig()
    , m_bThrowing(false)
{
    m_bDisableJump = true;
}

void PigWithBox::loadAnimation()
{
    Pig::loadAnimation();

    m_animations[IDLE] = std::make_unique<Animation>("pigWithBox idle", 26, 30, 9);
    m_animations[RUN] = std::make_unique<Animation>("pigWithBox run", 26, 30, 6);
    m_animations[THROWING] = std::make_unique<Animation>("pigWithBox throwing", 26, 30, 5);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void PigWithBox::update()
{
    if (isInvulnerable()) {
        becomeNormal();
        disappear();
        return;
    }
    Pig::update();
    if (isSeeing(PhysicWorld::CAT_PLAYER) && m_visionNearestDistance <= 100) {
        throwBox();
        becomeNormal();
    }
}

void PigWithBox::throwBox()
{
    auto pParams = std::make_unique<LoaderParams>(LoaderParams(
        getPosition().x - m_width / 2.0f,
        getPosition().y - m_height / 2.0f - 20,
        20,
        20));

    GameObject* box = Game::Instance().getLevel()->spawnGameObject("Box", std::move(pParams));
    box->getBody()->ApplyForce(
        b2Vec2(m_direction * 100, -32),
        box->getBody()->GetWorldCenter(),
        true);
}

void PigWithBox::becomeNormal()
{
    disappear();
    auto pParams2 = std::make_unique<LoaderParams>(
        LoaderParams(getPosition().x - (20 * 0.5f), getPosition().y - (20 * 0.5f), 20, 20));
    Game::Instance().getLevel()->spawnGameObject("Pig", std::move(pParams2));
}
