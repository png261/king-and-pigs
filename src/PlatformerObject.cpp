#include "PlatformerObject.h"

#include "Game.h"
#include "TextureManager.h"
#include <iostream>

#define GRAVITY 0.3

PlatformerObject::PlatformerObject()
    : GameObject(), m_moveSpeed(0), m_dyingTime(0), m_dyingCounter(0),
      m_bPlayedDeathSound(false), m_bFlipped(false), m_bMoveLeft(false),
      m_bMoveRight(false), m_bRunning(false), m_bFalling(false),
      m_bJumping(false), m_bCanJump(false), m_lastSafePos(0, 0) {
    m_acceleration.setY(GRAVITY);
}

void PlatformerObject::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

void PlatformerObject::draw() {
    TextureManager::Instance()->drawFrame(
        m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
        m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), m_angle,
        m_alpha, m_bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void PlatformerObject::update() {
    m_velocity += m_acceleration;

    // on ground
    if (m_position.getY() + m_velocity.getY() >= Game::Instance()->getGameHeight() - 400) {
        m_velocity.setY(0);
    } 

    m_position += m_velocity;

    if (m_velocity.getX() < 0) {
        m_bFlipped = true;
    } else if (m_velocity.getX() > 0) {
        m_bFlipped = false;
    }

    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
}

void PlatformerObject::doDyingAnimation() {
    m_currentFrame = int(((SDL_GetTicks() / (1000 / 10)) % m_numFrames));

    if (m_dyingCounter == m_dyingTime) {
        m_bDead = true;
    }
    m_dyingCounter++;
}
