#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <map>
#include <string>
#include <vector>
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Vector2D.h"

class TileLayer;

class GameObject
{
public:
    virtual ~GameObject(){};

    virtual void load(const LoaderParams* pParams) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual std::string type() = 0;

    Vector2D& getPosition() { return m_position; }
    Vector2D& getVelocity() { return m_velocity; }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    virtual void setAnimation(std::string textureID)
    {
        m_textureID = textureID;
        m_numFrames = TextureManager::Instance()->getNFrames(textureID);
    }

    // is the object currently being updated?
    bool updating() { return m_bUpdating; }
    bool invulnerable() { return m_bInvulnerable; }
    bool isAttack() { return m_bAttack; }

    // set whether to update the object or not
    void setUpdating(bool updating) { m_bUpdating = updating; }

    bool isDead() { return m_bDead; }

    bool isDying() { return m_bDying; }

    void setCollisionLayers(std::vector<TileLayer*>* layers) { m_pCollisionLayers = layers; }

protected:
    GameObject()
        : m_position(0, 0)
        , m_velocity(0, 0)
        , m_acceleration(0, 0)
        , m_width(0)
        , m_height(0)
        , m_textureHeight(0)
        , m_textureWidth(0)
        , m_currentRow(0)
        , m_currentFrame(0)
        , m_bUpdating(false)
        , m_angle(0)
        , m_bDead(false)
        , m_bAttack(false)
        , m_alpha(255)
        , m_bFlipped(false)
        , m_aniCounter(false)
        , m_bInvulnerable(false)
    {
        m_numFrames = TextureManager::Instance()->getNFrames(m_textureID);
    }

    // movement
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    // size
    int m_width;
    int m_height;
    int m_textureHeight;
    int m_textureWidth;

    // animation
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;
    int m_aniCounter;

    // common boolean
    bool m_bUpdating;

    // rotation
    double m_angle;
    bool m_bFlipped;

    bool m_bDead;
    bool m_bDying;
    int m_bAttack;

    bool m_bInvulnerable;

    int m_alpha;
    std::vector<TileLayer*>* m_pCollisionLayers;
};

#endif
