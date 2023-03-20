#include "Pig.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "PhysicWorld.hpp"

Pig::Pig()
    : Enemy()
    , DamageableObject(3, 300, 1000)
    , AttackableObject(1, 50, 300)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Enemy::load(std::move(pParams));
    m_moveSpeed = 50;
    m_jumpHeight = 32.0f;
    this->createAttackSensor(getBody(), m_width, PhysicWorld::MASK_ENEMY_ATTACK_SENSOR);
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

    Enemy::update();
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
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}
