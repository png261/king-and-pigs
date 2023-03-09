#include "Pig.hpp"
#include "Box2D.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

Pig::Pig()
    : Enemy()
    , DamageableObject(3, 300)
    , AttackableObject(1, 50, 300)
{}

void Pig::load(const LoaderParams* const pParams)
{
    Enemy::load(pParams);
    this->createAttackSensor(getBody(), m_width, Box2D::MASK_ENEMY_ATTACK_SENSOR);
    this->loadAnimation();

    m_currentAttackState = ON_NORMAL;
}

void Pig::loadAnimation()
{
    m_animations[Animation::IDLE] = new Animation("pig idle", 34, 28, 11);
    m_animations[Animation::RUN] = new Animation("pig run", 34, 28, 6);
    m_animations[Animation::JUMP] = new Animation("pig jump", 34, 28, 1);
    m_animations[Animation::FALL] = new Animation("pig fall", 34, 28, 1);
    m_animations[Animation::GROUND] = new Animation("pig ground", 34, 28, 1);
    m_animations[Animation::ATTACK] = new Animation("pig attack", 34, 28, 3, false);
    m_animations[Animation::HIT] = new Animation("pig hit", 34, 28, 2);
    m_animations[Animation::DEAD] = new Animation("pig dead", 34, 28, 4, false);

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Pig::update()
{
    Enemy::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();
}

void Pig::updateAnimation()
{
    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isInvulnerable()) {
        m_currentAttackState = ON_HIT;
    } else if (this->isAttack()) {
        m_currentAttackState = ON_ATTACK;
    } else if (this->isDead()) {
        m_currentAttackState = ON_DIE;
    } else {
        m_currentAttackState = ON_NORMAL;
    }

    switch (m_currentState) {
    case ON_GROUND:
        newAnimation = Animation::IDLE;
        break;
    case ON_FLY:
        if (this->getBody()->GetLinearVelocity().y == 0) {
            m_currentState = ON_GROUND;
            break;
        }

        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = Animation::JUMP;
        } else {
            newAnimation = Animation::FALL;
        }
        break;
    }

    switch (m_currentAttackState) {
    case ON_NORMAL:
        if (InputHandler::Instance()->isKeyPressed(KEY_S)) {
            this->attack();
            break;
        }

        break;
    case ON_HIT:
        newAnimation = Animation::HIT;
        break;
    case ON_ATTACK:
        newAnimation = Animation::ATTACK;
        break;
    case ON_DIE:
        newAnimation = Animation::DEAD;
        break;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}
