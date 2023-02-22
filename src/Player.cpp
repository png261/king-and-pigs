#include <box2d/b2_fixture.h>
#include <iostream>
#include "Animation.hpp"
#include "Box2D.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "PlatformerObject.hpp"
#include "SoundManager.hpp"

void Player::load(const LoaderParams* pParams)
{
    m_moveSpeed = 6 * Box2D::PPM;
    m_jumpSpeed = -6 * Box2D::PPM;
    m_attackDamage = 1;
    m_attackRange = 100;

    PlatformerObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_PLAYER;
    filter.maskBits = Box2D::MASK_PLAYER;
    m_pFixture->SetFilterData(filter);

    b2Filter attackFilter;
    attackFilter.categoryBits = Box2D::CAT_ATTACK_SENSOR;
    attackFilter.maskBits = Box2D::MASK_PLAYER_ATTACK_SENSOR;
    m_pAttackSensor->SetFilterData(attackFilter);

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
            float impulse = -m_pBody->GetMass() * 100 * Box2D::PPM;
            m_pBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_pBody->GetWorldCenter(), 1);
        }
        break;
    case ON_FLY: newAnimation = JUMP; break;
    case ON_FALL: newAnimation = FALL; break;
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
