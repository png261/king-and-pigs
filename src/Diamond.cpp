#include "Diamond.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"

void Diamond::load(std::unique_ptr<LoaderParams> const& pParams)
{
    ItemObject::load(pParams);
    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);
    loadAnimation();
}

void Diamond::loadAnimation()
{
    m_animations[NORMAL] = std::make_unique<Animation>("diamond idle", 18, 14, 7);
    m_animations[HIT] = std::make_unique<Animation>("diamond hit", 18, 14, 2, false);

    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
}

void Diamond::update()
{
    ItemObject::update();
    if (m_curAnimation == HIT && m_animations[m_curAnimation]->isFinished()) {
        disappear();
    }
}

void Diamond::bonus()
{
    SoundManager::Instance().playSFX("heart bonus");
    Game::Instance().addDiamond(+1);
    m_curAnimation = HIT;
    m_animations[m_curAnimation]->start();
}
