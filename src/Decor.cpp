#include "Decor.hpp"

void Decor::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);
    m_animations[Animation::IDLE] = new Animation("candle idle", 14, 32, 8);
    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);
};
