#include "PlatformerObject.h"

#include <iostream>
#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "TileLayer.h"

#define GRAVITY 0.3

PlatformerObject::PlatformerObject()
    : GameObject()
    , m_bAttack(false)
    , m_startState(0)
    , m_bInvulnerable(false)
{
    m_acceleration.setY(GRAVITY);
}

void PlatformerObject::load(const LoaderParams* pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();

    m_textureID = pParams->getTextureID();

    m_textureWidth = pParams->getTextureWidth();
    m_textureHeight = pParams->getTextureHeight();
    m_textureX = pParams->getTextureX();
    m_textureY = pParams->getTextureY();
    m_numFrames = pParams->getNumFrames();

    m_lives = pParams->getLives();
    m_maxLives = m_lives;
}

void PlatformerObject::draw()
{
    TextureManager::Instance()->drawFrame(
        m_textureID,
        m_position.getX() - TheCamera::Instance()->getPosition().m_x,
        m_position.getY() - TheCamera::Instance()->getPosition().m_y,
        m_textureWidth,
        m_textureHeight,
        m_textureX,
        m_textureY,
        m_currentRow,
        m_currentFrame,
        Game::Instance()->getRenderer(),
        m_angle,
        m_alpha,
        m_bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    // debug
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = m_width;
    srcRect.h = destRect.h = m_height;
    destRect.x = m_position.getX() - TheCamera::Instance()->getPosition().m_x;
    destRect.y = m_position.getY() - TheCamera::Instance()->getPosition().m_y;

    SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 255, 255);
    SDL_RenderDrawRect(Game::Instance()->getRenderer(), &destRect);
    SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0, 0, 0, 255);
    //
}

void PlatformerObject::update()
{
    if (m_lives <= 0) {
        m_currentAttackState = ON_DIE;
    }
    m_velocity += m_acceleration;
    handleMovement(m_velocity);

    if (m_velocity.getX() < 0) {
        m_bFlipped = true;
    } else if (m_velocity.getX() > 0) {
        m_bFlipped = false;
    }

    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
}

void PlatformerObject::handleMovement(Vector2D velocity)
{
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

bool PlatformerObject::checkCollideTile(Vector2D newPos)
{
    for (auto& pTileLayer : *m_pCollisionLayers) {
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

        Vector2D layerPos = pTileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileid = 0;

        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();

        Vector2D startPos = newPos;
        Vector2D endPos(newPos.m_x + (m_width), (newPos.m_y) + m_height);

        for (int i = startPos.m_x; i < endPos.m_x; i++) {
            for (int j = startPos.m_y; j < endPos.m_y; j++) {
                tileColumn = i / pTileLayer->getTileSize();
                tileRow = j / pTileLayer->getTileSize();

                const int EMPTY_TILE = 0;
                if (tiles[tileRow + y][tileColumn + x] != EMPTY_TILE) {
                    return true;
                }
            }
        }
    }

    return false;
}
