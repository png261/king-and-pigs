#include "Player.h"

#include "InputHandler.h"
#include "SoundManager.h"
#include <SDL2/SDL_scancode.h>
#include <iostream>

Player::Player() : PlatformerObject() {
    m_nFrameMap["player idle"] = 11;
    m_nFrameMap["player run"] = 8;
    m_nFrameMap["player jump"] = 1;
    m_nFrameMap["player fall"] = 1;
    m_nFrameMap["player ground"] = 1;
    m_nFrameMap["player attack"] = 3;
    m_nFrameMap["player hit"] = 2;
    m_nFrameMap["player dead"] = 4;
    m_nFrameMap["player doorIn"] = 8;
    m_nFrameMap["player doorOut"] = 8;
}

void Player::load(const LoaderParams *pParams) {
    PlatformerObject::load(pParams);

    m_moveSpeed = 2;
    m_jumpSpeed = 7;

    m_dyingTime = 100;
    m_currentState = ON_FLY;
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
