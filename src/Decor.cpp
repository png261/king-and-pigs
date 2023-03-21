#include "Decor.hpp"

void Decor::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);

    m_animations[Animation::IDLE] =
        std::make_unique<Animation>(Animation("candle idle", 14, 32, 8));
    m_curAnimation = Animation::IDLE;

    m_animations[m_curAnimation]->start();

    m_pBody->SetGravityScale(0);
    m_pFixture->SetSensor(true);
};
