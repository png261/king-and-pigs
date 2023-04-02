#include "Heart.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"

void Heart::load(std::unique_ptr<LoaderParams> const& pParams)
{
    ItemObject::load(pParams);
    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);
    this->loadAnimation();
}

void Heart::loadAnimation()
{
    m_animations[NORMAL] = new Animation("heart idle", 18, 14, 7);
    m_animations[HIT] = new Animation("heart hit", 18, 14, 2, false);

    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
}

void Heart::update()
{
    ItemObject::update();
    if (m_curAnimation == HIT && m_animations[m_curAnimation]->isFinished()) {
        SoundManager::Instance()->playSFX("heart bonus");
        Game::Instance()->getLevel()->getPlayer()->heal(1);
        this->disappear();
    }
}

void Heart::bonus()
{
    m_curAnimation = HIT;
    m_animations[m_curAnimation]->start();
}
