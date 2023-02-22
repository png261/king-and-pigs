#include "Enemy.hpp"

#include "Box2D.hpp"

void Enemy::load(const LoaderParams* pParams)
{
    m_attackDamage = 1;
    m_attackRange = 100;

    PlatformerObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_ENEMY;
    filter.maskBits = Box2D::MASK_ENEMY;
    m_pFixture->SetFilterData(filter);

    b2Filter attackFilter;
    attackFilter.categoryBits = Box2D::CAT_ATTACK_SENSOR;
    attackFilter.maskBits = Box2D::MASK_ENEMY_ATTACK_SENSOR;
    m_pAttackSensor->SetFilterData(attackFilter);
};

void Enemy::draw()
{
    PlatformerObject::draw();
}
