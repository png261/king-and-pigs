#include "Box.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

Box::Box()
    : GameObject()
    , DamageableObject(1, 200, 100)
{}

void Box::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_BOX;
    filter.maskBits = PhysicWorld::MASK_BOX;
    m_pFixture->SetFilterData(filter);
    m_pBody->SetFixedRotation(false);

    this->loadAnimation();
}

void Box::loadAnimation()
{
    m_animations[NORMAL] = new Animation("box idle", 22, 16, 1);
    m_animations[HIT] = new Animation("box hit", 22, 16, 2);

    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    if (this->isDead()) {
        /* this->breakIntoPieces(); */
        this->disappear();
        return;
    }

    GameObject::update();
    DamageableObject::update();
    this->updateAnimation();
}

void Box::updateAnimation()
{
    int newAnimation = m_curAnimation;

    if (this->isDying()) {
        newAnimation = HIT;
    } else {
        newAnimation = NORMAL;
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
