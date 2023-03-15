#include "Enemy.hpp"

#include "PhysicWorld.hpp"

void Enemy::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ENEMY;
    filter.maskBits = PhysicWorld::MASK_ENEMY;
    m_pFixture->SetDensity(50);
    m_pFixture->SetFilterData(filter);
};
