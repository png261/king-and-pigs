#include "AttackableObject.hpp"
#include "PhysicWorld.hpp"
AttackableObject::AttackableObject(const int damage, const int range, const int attackSpeed)
    : m_damage(damage)
    , m_range(range)
    , m_bAttack(false)
    , m_bCanAttack(true)
    , m_bTurnRight(true)
    , m_attackSpeed(attackSpeed)
    , m_pAttackSensor(nullptr)
    , attackTimer(attackSpeed)
{}

void AttackableObject::createAttackSensor(
    b2Body* const pBody,
    const int objectWidth,
    const PhysicWorld::FilterMask filterMask)
{
    b2PolygonShape attackShape;
    attackShape.SetAsBox(
        PhysicWorld::pixelToMeter(m_range) / 2.0f,
        PhysicWorld::pixelToMeter(m_range) / 2.0f,
        b2Vec2(-(PhysicWorld::pixelToMeter(objectWidth) / 4.0f + PhysicWorld::pixelToMeter(m_range) / 2.0f), 0),
        0);

    b2FixtureDef attackSensorDef;
    attackSensorDef.shape = &attackShape;
    attackSensorDef.filter.categoryBits = PhysicWorld::CAT_ATTACK_SENSOR;
    attackSensorDef.filter.maskBits = filterMask;
    attackSensorDef.isSensor = true;
    attackSensorDef.userData.pointer = reinterpret_cast<uintptr_t>((void*)"left");

    m_pAttackSensor = pBody->CreateFixture(&attackSensorDef);

    attackShape.SetAsBox(
        PhysicWorld::pixelToMeter(m_range) / 2.0f,
        PhysicWorld::pixelToMeter(m_range) / 2.0f,
        b2Vec2((PhysicWorld::pixelToMeter(objectWidth) / 4.0f + PhysicWorld::pixelToMeter(m_range) / 2.0f), 0),
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
    attackTimer.restart();
}

void AttackableObject::update()
{
    if (attackTimer.isDone()) {
        m_bAttack = false;
        m_bCanAttack = true;
    }
}
