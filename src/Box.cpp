#include "Box.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"
#include "Utils.hpp"

Box::Box()
    : GameObject()
    , DamageableObject(1, 200, 100)
{}

void Box::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    createBody(pParams->x(), pParams->y(), m_width, m_height);

    setFilterData(PhysicWorld::CAT_BOX, PhysicWorld::MASK_BOX);
    m_pBody->SetFixedRotation(false);

    loadAnimation();
}

void Box::loadAnimation()
{
    m_animations[NORMAL] = std::make_unique<Animation>("box idle", 22, 16, 1);
    m_animations[HIT] = std::make_unique<Animation>("box hit", 22, 16, 2);

    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    if (isDead()) {
        /* breakIntoPieces(); */
        randomBonus();
        SoundManager::Instance().playSFX("box broken");
        disappear();
        return;
    }

    GameObject::update();
    DamageableObject::update();
    updateAnimation();
}

void Box::updateAnimation()
{
    int newAnimation = m_curAnimation;

    if (isDying()) {
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
    auto pParams = std::make_unique<LoaderParams>(
        LoaderParams(getPosition().x - 10 / 2.0f, getPosition().y - 10 / 2.0f - 20, 10, 10));

    Game::Instance().getLevel()->spawnGameObject("Box", std::move(pParams));
    Game::Instance().getLevel()->spawnGameObject("Box", std::move(pParams));
    Game::Instance().getLevel()->spawnGameObject("Box", std::move(pParams));
    Game::Instance().getLevel()->spawnGameObject("Box", std::move(pParams));
}

void Box::randomBonus()
{
    auto pParams =
        std::make_unique<LoaderParams>(LoaderParams(getPosition().x, getPosition().y, 10, 10));
    if (Utils::isProbable(30)) {
        Game::Instance().getLevel()->spawnGameObject("Heart", std::move(pParams));
        return;
    }

    if (Utils::isProbable(10)) {
        Game::Instance().getLevel()->spawnGameObject("Diamond", std::move(pParams));
        return;
    }
}
