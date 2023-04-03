#include "Candle.hpp"

void Candle::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);

    m_pBody->SetGravityScale(0);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_NONE;
    m_pFixture->SetFilterData(filter);
    m_pFixture->SetSensor(true);
    this->loadAnimation();
};

void Candle::loadAnimation()
{
    m_animations[NORMAL] = std::make_unique<Animation>("candle idle", 14, 32, 8);
    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
}
