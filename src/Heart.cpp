#include "Heart.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

void Heart::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("heart idle", 18, 14, 7));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("heart hit", 18, 14, 2));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Heart::bonus()
{
    m_curAnimation = Animation::HIT;
    m_animations[m_curAnimation]->start();
    this->disappear();
}
