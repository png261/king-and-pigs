#include "Player.h"

#include "InputHandler.h"
#include "SoundManager.h"
#include <SDL2/SDL_scancode.h>
#include <iostream>

Player::Player()
    : PlatformerObject(), m_invulnerable(false), m_invulnerableTime(200),
      m_invulnerableCounter(0) {}

void Player::load(const LoaderParams *pParams) {
    PlatformerObject::load(pParams);

    m_moveSpeed = 3;

    m_dyingTime = 100;
}

void Player::draw() { PlatformerObject::draw(); }

void Player::handleAnimation() {}

void Player::update() {
    m_velocity.setX(0);
    m_velocity.setY(0);
    handleInput();
    PlatformerObject::update();
}

void Player::ressurect() {}

void Player::collision() {}

void Player::clean() {}

void Player::handleInput() {}
