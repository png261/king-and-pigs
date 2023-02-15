
#include <iostream>

#include "Camera.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlatformerObject.h"
#include "SoundManager.h"

Player::Player()
    : PlatformerObject()
{}

void Player::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);

    m_moveSpeed = 2;
    m_jumpSpeed = 7;
    m_damage = 1;
    m_damageRange = 10;

    m_currentState = ON_FLY;
    m_currentAttackState = ON_NORMAL;
    TheCamera::Instance()->setTarget(this);
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
    switch (m_currentState) {
    case ON_GROUND:
        if (m_currentAttackState == ON_HIT) {
            break;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
            m_velocity.setX(-m_moveSpeed);
            setAnimation("player run");
        } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
            m_velocity.setX(m_moveSpeed);
            setAnimation("player run");
        } else {
            m_velocity.setX(0);
            setAnimation("player idle");
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            m_velocity.setY(-m_jumpSpeed);
            setAnimation("player jump");
            m_currentState = ON_FLY;
        }
        break;
    case ON_FLY:
        if (m_velocity.getY() > 0) {
            m_currentState = ON_FALL;
            break;
        }

        if (m_velocity.getY() < 0) {
            setAnimation("player jump");
            break;
        }
        break;
    case ON_FALL:
        setAnimation("player fall");
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
        if (m_startState == 0) {
            m_startState = SDL_GetTicks();
        }
        if (m_startState && SDL_GetTicks() - m_startState >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_startState = 0;
            m_bInvulnerable = false;
            m_velocity.setX(0);
            break;
        }

        m_bInvulnerable = true;
        setAnimation("player hit");
        break;
    case ON_ATTACK:
        if (m_startState == 0) {
            m_startState = SDL_GetTicks();
        }
        if (SDL_GetTicks() - m_startState >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_startState = 0;
            m_bAttack = false;
            break;
        }

        m_bAttack = true;
        setAnimation("player attack");
        break;
    case ON_DIE: setAnimation("player die"); break;
    }
};

void Player::ressurect() {}

void Player::clean() {}
