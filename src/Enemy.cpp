#include "Enemy.hpp"

#include "PhysicWorld.hpp"

void Enemy::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ENEMY;
    filter.maskBits = PhysicWorld::MASK_ENEMY;
    m_pFixture->SetDensity(50);
    m_pFixture->SetFilterData(filter);
};
