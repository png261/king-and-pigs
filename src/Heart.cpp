#include "Heart.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

void Heart::load(std::unique_ptr<LoaderParams> const& pParams)
{
    ItemObject::load(pParams);
    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);
    this->loadAnimation();
}

void Heart::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("heart idle", 18, 14, 7));
    m_animations[Animation::HIT] =
        std::make_unique<Animation>(Animation("heart hit", 18, 14, 2, false));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Heart::update()
{
    ItemObject::update();
    if (m_curAnimation == Animation::HIT && m_animations[m_curAnimation]->isFinished()) {
        Game::Instance()->getLevel()->getPlayer()->heal(1);
        this->disappear();
    }
}

void Heart::bonus()
{
    m_curAnimation = Animation::HIT;
    m_animations[m_curAnimation]->start();
}
