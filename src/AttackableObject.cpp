#include "AttackableObject.hpp"
AttackableObject::AttackableObject(const int damage, const int range, const int attackSpeed)
    : m_damage(damage)
    , m_range(range)
    , m_bAttack(false)
    , m_bCanAttack(true)
    , m_bTurnRight(true)
    , m_attackSpeed(attackSpeed)
    , m_pAttackSensor(nullptr)
{}

void AttackableObject::createAttackSensor(
    b2Body* const pBody,
    const int objectWidth,
    const Box2D::FilterMask filterMask)
{
    b2PolygonShape attackShape;
    attackShape.SetAsBox(
        m_range / 2.0f,
        m_range / 2.0f,
        b2Vec2(-(objectWidth / 4.0f + m_range / 2.0f), 0),
        0);

    b2FixtureDef attackSensorDef;
    attackSensorDef.shape = &attackShape;
    attackSensorDef.filter.categoryBits = Box2D::CAT_ATTACK_SENSOR;
    attackSensorDef.filter.maskBits = filterMask;
    attackSensorDef.isSensor = true;
    attackSensorDef.userData.pointer = reinterpret_cast<uintptr_t>((void*)"left");

    m_pAttackSensor = pBody->CreateFixture(&attackSensorDef);

    attackShape.SetAsBox(
        m_range / 2.0f,
        m_range / 2.0f,
        b2Vec2((objectWidth / 4.0f + m_range / 2.0f), 0),
        0);
    attackSensorDef.userData.pointer = reinterpret_cast<uintptr_t>((void*)"right");
    m_pAttackSensor = pBody->CreateFixture(&attackSensorDef);
}

bool AttackableObject::isAttack() const
{
    return m_bAttack;
}

bool AttackableObject::isTurnRight() const
{
    return m_bTurnRight;
}

bool AttackableObject::canAttack() const
{
    return m_bCanAttack;
}

int AttackableObject::getDamage() const
{
    return m_damage;
}

void AttackableObject::attack()
{
    if (isAttack() || canAttack() == false) {
        return;
    }

    m_bAttack = true;
    m_bCanAttack = false;
    attackTimer.start();
}

void AttackableObject::update()
{
    if (attackTimer.delta() >= m_attackSpeed) {
        m_bAttack = false;
        m_bCanAttack = true;
        attackTimer.stop();
    }
}
