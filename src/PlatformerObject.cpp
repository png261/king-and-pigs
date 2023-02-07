#include "PlatformerObject.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "TileLayer.h"
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
        m_textureID,
        m_position.getX() - TheCamera::Instance()->getPosition().m_x,
        m_position.getY() - TheCamera::Instance()->getPosition().m_y, m_width,
        m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(),
        m_angle, m_alpha, m_bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void PlatformerObject::update() {
    m_velocity += m_acceleration;
    handleMovement(m_velocity);

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

void PlatformerObject::handleMovement(Vector2D velocity) {
    // get the current position
    Vector2D newPos = m_position;

    newPos.m_x = m_position.m_x + velocity.m_x;
    if (checkCollideTile(newPos)) {
        m_velocity.m_x = 0;
    } else {
        m_position.m_x = newPos.m_x;
    }

    newPos = m_position;

    newPos.m_y += velocity.m_y;
    if (checkCollideTile(newPos)) {
        m_velocity.m_y = 0;
    } else {
        m_position.m_y = newPos.m_y;
    }
}

bool PlatformerObject::checkCollideTile(Vector2D newPos) {
    if (newPos.m_y + m_height >= TheGame::Instance()->getGameHeight() - 32) {
        return false;
    } else {
        for (auto &pTileLayer : *m_pCollisionLayers) {
            std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

            Vector2D layerPos = pTileLayer->getPosition();

            int x, y, tileColumn, tileRow, tileid = 0;

            x = layerPos.getX() / pTileLayer->getTileSize();
            y = layerPos.getY() / pTileLayer->getTileSize();

            Vector2D startPos = newPos;
            startPos.m_x += 15;
            startPos.m_y += 20;
            Vector2D endPos(newPos.m_x + (m_width - 15),
                            (newPos.m_y) + m_height - 4);

            for (int i = startPos.m_x; i < endPos.m_x; i++) {
                for (int j = startPos.m_y; j < endPos.m_y; j++) {
                    tileColumn = i / pTileLayer->getTileSize();
                    tileRow = j / pTileLayer->getTileSize();

                    if (tiles[tileRow + y][tileColumn + x] != 0) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}
