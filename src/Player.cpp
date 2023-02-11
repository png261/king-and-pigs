#include "Player.h"

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

    m_currentState = ON_FLY;
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

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
            setAnimation("player attack");
            m_bAttack = true;
        } else {
            m_bAttack = false;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            m_velocity.setY(-m_jumpSpeed);
            setAnimation("player jump");
            m_currentState = ON_FLY;
        }
        break;
    case ON_FLY:
        if (m_velocity.getY() > 0) {
            setAnimation("player fall");
            m_currentState = ON_FALL;
        } else if (m_velocity.getY() < 0) {
            setAnimation("player jump");
        }
        break;
    case ON_FALL:
        if (m_velocity.getY() == 0) {
            setAnimation("player ground");
            m_currentState = ON_GROUND;
        }
        break;
    case ON_HIT:
        if (m_aniCounter >= 50) {
            m_aniCounter = 0;
            m_currentState = ON_GROUND;
            m_bInvulnerable = false;
            m_velocity.setX(0);
            break;
        }
        m_bInvulnerable = true;
        m_velocity.setY(5);
        m_velocity.setX(1);
        setAnimation("player hit");
        break;
    case ON_ATTACK: break;
    }

    m_aniCounter++;
};

void Player::ressurect() {}

void Player::clean() {}
