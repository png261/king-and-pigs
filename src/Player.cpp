#include <iostream>
#include "Animation.hpp"
#include "Box2d.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "PlatformerObject.hpp"
#include "SoundManager.hpp"

void Player::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);

    m_moveSpeed = 6 * Box2d::PPM;
    m_jumpSpeed = -6 * Box2d::PPM;
    m_damage = 1;
    m_damageRange = 10;

    m_animations[IDLE] = new Animation("player idle", 11);
    m_animations[RUN] = new Animation("player run", 8);
    m_animations[JUMP] = new Animation("player jump", 1);
    m_animations[FALL] = new Animation("player fall", 1);
    m_animations[GROUND] = new Animation("player ground", 1);
    m_animations[ATTACK] = new Animation("player attack", 3);
    m_animations[HIT] = new Animation("player hit", 2);
    m_animations[DEAD] = new Animation("player dead", 4, false);
    m_animations[DOOR_IN] = new Animation("player door in", 8, false);
    m_animations[DOOR_OUT] = new Animation("player door out", 8, false);

    m_currentState = ON_GROUND;
    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
    m_currentAttackState = ON_NORMAL;
}

void Player::draw()
{
    PlatformerObject::draw();
}

void Player::update()
{
    handleInput();
    PlatformerObject::update();
}

void Player::handleInput()
{
    ANIMATION_ID newAnimation;
    switch (m_currentState) {
    case ON_GROUND:
        if (isDead() || m_currentAttackState == ON_HIT) {
            break;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
            float impulse = -m_pBody->GetMass() * 6;
            m_pBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pBody->GetWorldCenter(), 1);
            newAnimation = RUN;
        } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
            float impulse = m_pBody->GetMass() * 6;
            m_pBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pBody->GetWorldCenter(), 1);
            newAnimation = RUN;
        } else {
            newAnimation = IDLE;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            float impulse = -m_pBody->GetMass() * 20;
            m_pBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_pBody->GetWorldCenter(), 1);
            /* m_currentState = ON_FLY; */
        }
        break;
    case ON_FLY:
        if (m_velocity.getY() > 0) {
            m_currentState = ON_FALL;
            break;
        }

        if (m_velocity.getY() < 0) {
            newAnimation = JUMP;
            break;
        }
        break;
    case ON_FALL:
        newAnimation = FALL;
        if (m_velocity.getY() == 0) {
            m_currentState = ON_GROUND;
        }
        break;
    }

    switch (m_currentAttackState) {
    case ON_NORMAL:
        if (m_lives <= 0) {
            m_currentAttackState = ON_DIE;
            break;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
            m_currentAttackState = ON_ATTACK;
            break;
        }

        break;
    case ON_HIT:
        timer.start();

        if (timer.delta() >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_bInvulnerable = false;
            m_velocity.setX(0);
            timer.stop();
            break;
        }

        m_bInvulnerable = true;
        newAnimation = HIT;
        break;
    case ON_ATTACK:
        timer.start();

        if (timer.delta() >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_bAttack = false;
            timer.stop();
            break;
        }

        m_bAttack = true;
        newAnimation = ATTACK;
        break;
    case ON_DIE: newAnimation = DEAD; break;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
};

void Player::clean() {}
