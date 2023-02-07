#include "Player.h"

#include "Camera.h"
#include "Game.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include <iostream>

Player::Player() : PlatformerObject() {}

void Player::load(const LoaderParams *pParams) {
    PlatformerObject::load(pParams);

    m_moveSpeed = 2;
    m_jumpSpeed = 7;

    m_dyingTime = 100;
    m_currentState = ON_FLY;
    TheCamera::Instance()->setTarget(this);
}

void Player::draw() { PlatformerObject::draw(); }

void Player::handleAnimation() {}

void Player::update() {
    handleInput();
    PlatformerObject::update();
}

void Player::handleInput() {
    if (m_currentState == ON_GROUND) {
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
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            m_velocity.setY(-m_jumpSpeed);
            setAnimation("player jump");
            m_currentState = ON_FLY;
        }
    } else if (m_currentState == ON_FLY) {
        if (m_velocity.getY() > 0) {
            setAnimation("player fall");
        } else if (m_velocity.getY() < 0) {
            setAnimation("player jump");
        } else if (m_velocity.getY() == 0) {
            setAnimation("player ground");
            m_currentState = ON_GROUND;
        }
    }
};

void Player::ressurect() {}

void Player::collision() {}

void Player::clean() {}
