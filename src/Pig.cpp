#include "Pig.hpp"
#include <iostream>
#include "Box2D.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

Pig::Pig()
    : Enemy()
    , DamageableObject(3, 300)
    , AttackableObject(1, 50, 300)
{}

void Pig::load(const LoaderParams* pParams)
{
    Enemy::load(pParams);
    this->createAttackSensor(getBody(), m_width, Box2D::MASK_ENEMY_ATTACK_SENSOR);

    m_animations[IDLE] = new Animation("pig idle", 11);
    m_animations[RUN] = new Animation("pig run", 6);
    m_animations[JUMP] = new Animation("pig jump", 1);
    m_animations[FALL] = new Animation("pig fall", 1);
    m_animations[GROUND] = new Animation("pig ground", 1);
    m_animations[ATTACK] = new Animation("pig attack", 3, false);
    m_animations[HIT] = new Animation("pig hit", 2);
    m_animations[DEAD] = new Animation("pig dead", 4, false);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
    m_currentAttackState = ON_NORMAL;
}

void Pig::update()
{
    Enemy::update();
    DamageableObject::update();
    AttackableObject::update();
    updateAnimation();
}

void Pig::updateAnimation()
{
    ANIMATION_ID newAnimation = m_curAnimation;

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
    case ON_GROUND: newAnimation = IDLE; break;
    case ON_FLY: newAnimation = JUMP; break;
    case ON_FALL: newAnimation = FALL; break;
    }

    switch (m_currentAttackState) {
    case ON_NORMAL:
        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
            this->attack();
            break;
        }

        break;
    case ON_HIT: newAnimation = HIT; break;
    case ON_ATTACK: newAnimation = ATTACK; break;
    case ON_DIE: newAnimation = DEAD; break;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}

void Pig::draw()
{
    Enemy::draw();
}
