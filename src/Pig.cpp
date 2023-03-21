#include "Pig.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "PhysicWorld.hpp"

Pig::Pig()
    : GameObject()
    , DamageableObject(3, 300, 1000)
    , AttackableObject(1, 25, 300)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ENEMY;
    filter.maskBits = PhysicWorld::MASK_ENEMY;
    m_pFixture->SetDensity(50);
    m_pFixture->SetFilterData(filter);

    m_moveSpeed = 50;
    m_jumpHeight = 32.0f;

    PhysicWorld::Instance()->createCircleSensor(
        m_pBody,
        -b2Vec2((m_width * 0.5 + m_range) * 0.5, 0),
        m_range,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_ENEMY_ATTACK_SENSOR);

    PhysicWorld::Instance()->createCircleSensor(
        m_pBody,
        b2Vec2((m_width * 0.5 + m_range) * 0.5, 0),
        m_range,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_ENEMY_ATTACK_SENSOR);

    this->loadAnimation();
}

void Pig::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("pig idle", 34, 28, 11));
    m_animations[Animation::RUN] = std::make_unique<Animation>(Animation("pig run", 34, 28, 6));
    m_animations[Animation::JUMP] = std::make_unique<Animation>(Animation("pig jump", 34, 28, 1));
    m_animations[Animation::FALL] = std::make_unique<Animation>(Animation("pig fall", 34, 28, 1));
    m_animations[Animation::GROUND] =
        std::make_unique<Animation>(Animation("pig ground", 34, 28, 1));
    m_animations[Animation::ATTACK] =
        std::make_unique<Animation>(Animation("pig attack", 34, 28, 3, false));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("pig hit", 34, 28, 2));
    m_animations[Animation::DYING] =
        std::make_unique<Animation>(Animation("pig dead", 34, 28, 4, false));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Pig::update()
{
    if (this->isDead()) {
        this->disappear();
        return;
    }

    GameObject::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();
}

void Pig::updateAnimation()
{
    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isOnGround()) {
        newAnimation = Animation::IDLE;
    } else {
        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = Animation::JUMP;
        } else {
            newAnimation = Animation::FALL;
        }
    }

    if (this->isInvulnerable()) {
        newAnimation = Animation::HIT;
    } else if (this->isAttack()) {
        newAnimation = Animation::ATTACK;
    } else if (this->isDying()) {
        newAnimation = Animation::DYING;
    }

    if (newAnimation != m_curAnimation) {
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}
