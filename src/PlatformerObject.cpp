#include "PlatformerObject.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

#define GRAVITY 0.3

PlatformerObject::PlatformerObject()
    : GameObject()
    , m_bAttack(false)
    , m_bInvulnerable(false)
{
    m_acceleration.setY(GRAVITY);
}

void PlatformerObject::load(const LoaderParams* pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();

    m_textureWidth = pParams->getTextureWidth();
    m_textureHeight = pParams->getTextureHeight();
    m_textureX = pParams->getTextureX();
    m_textureY = pParams->getTextureY();

    m_lives = pParams->getLives();
    m_maxLives = m_lives;
}

void PlatformerObject::draw()
{
    m_animations[m_curAnimation]->draw(
        m_position.getX() + m_textureX - TheCamera::Instance()->getPosition().m_x,
        m_position.getY() + m_textureY - TheCamera::Instance()->getPosition().m_y,
        m_textureWidth,
        m_textureHeight,
        m_bFlipped);
}

void PlatformerObject::update()
{
    if (getLives() <= 0) {
        m_currentAttackState = ON_DIE;
    }

    m_velocity += m_acceleration;
    handleMovement(m_velocity);

    if (m_velocity.getX() < 0) {
        m_bFlipped = true;
    } else if (m_velocity.getX() > 0) {
        m_bFlipped = false;
    }
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

std::string PlatformerObject::type()
{
    return "GameObject";
}

bool PlatformerObject::isInvulnerable()
{
    return m_bInvulnerable;
}

void PlatformerObject::setLives(int lives)
{
    m_lives = std::max(std::min(lives, m_maxLives), 0);
}

void PlatformerObject::changeLives(int lives)
{
    setLives(m_lives + lives);
}

int PlatformerObject::getLives()
{
    return m_lives;
}

void PlatformerObject::hit(int damage)
{
    if (isInvulnerable()) {
        return;
    }

    m_currentAttackState = ON_HIT;
    changeLives(-damage);
};

void PlatformerObject::attack(PlatformerObject* pTarget)
{
    pTarget->hit(1);
};
bool PlatformerObject::isAttack()
{
    return m_bAttack;
}

int PlatformerObject::getDamageRange()
{
    return m_damageRange;
}

bool PlatformerObject::isFlipped()
{
    return m_bFlipped;
}

void PlatformerObject::setCurrentState(objectMotion state)
{
    m_currentState = state;
}
