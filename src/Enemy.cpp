#include "Enemy.hpp"

#include "Box2D.hpp"

void Enemy::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_ENEMY;
    filter.maskBits = Box2D::MASK_ENEMY;
    m_pFixture->SetFilterData(filter);
};

void Enemy::draw()
{
    PlatformerObject::draw();
}
