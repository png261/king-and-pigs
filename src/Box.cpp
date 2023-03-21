#include "Box.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

Box::Box()
    : GameObject()
    , DamageableObject(2, 200, 300)
{}

void Box::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ENEMY;
    m_pFixture->SetFilterData(filter);

    m_pBody->SetFixedRotation(false);
    m_pFixture->SetDensity(0.5);
    m_pFixture->SetFriction(0.3);

    this->loadAnimation();
}

void Box::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("box idle", 22, 16, 1));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("box hit", 22, 16, 2));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    if (this->isDead()) {
        this->breakIntoPieces();
        this->disappear();
        return;
    }

    GameObject::update();
    DamageableObject::update();
    this->updateAnimation();
}

void Box::updateAnimation()
{
    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isInvulnerable()) {
        newAnimation = Animation::HIT;
    } else {
        newAnimation = Animation::IDLE;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}

void Box::breakIntoPieces()
{
    std::unique_ptr<LoaderParams> pParams = std::make_unique<LoaderParams>(LoaderParams(
        this->getPosition().x - 10 / 2.0f,
        this->getPosition().y - 10 / 2.0f - 20,
        10,
        10));

    Game::Instance()->getLevel()->spawnGameObject("Box", std::move(pParams));
    Game::Instance()->getLevel()->spawnGameObject("Box", std::move(pParams));
    Game::Instance()->getLevel()->spawnGameObject("Box", std::move(pParams));
    Game::Instance()->getLevel()->spawnGameObject("Box", std::move(pParams));
}
