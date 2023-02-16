#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <map>
#include <string>
#include <vector>
#include "LoaderParams.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"

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

    Vector2D& getPosition();
    Vector2D& getVelocity();

    int getWidth() const;
    int getHeight() const;

    bool isUpdating() const;
    bool isDead() const;

    void setUpdating(bool updating);
    void setCollisionLayers(std::vector<TileLayer*>* layers);

protected:
    GameObject();

    // movement
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    // size
    int m_width;
    int m_height;

    int m_textureHeight;
    int m_textureWidth;
    int m_textureX;
    int m_textureY;

    bool m_bUpdating;

    double m_angle;
    bool m_bFlipped;

    bool m_bDead;

    std::vector<TileLayer*>* m_pCollisionLayers;
};

#endif
