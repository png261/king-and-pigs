#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <box2d/box2d.h>
#include <map>
#include <string>
#include <vector>
#include "LoaderParams.hpp"
#include "TextureManager.hpp"

class TileLayer;

class GameObject
{
public:
    virtual ~GameObject(){};

    virtual void load(const LoaderParams* pParams);
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual std::string type() = 0;

    b2Vec2& getPosition();
    b2Vec2& getVelocity();

    int getWidth() const;
    int getHeight() const;

    bool isUpdating() const;
    bool isDead() const;

    void setUpdating(bool updating);

protected:
    GameObject();

    // movement
    b2Vec2 m_position;
    b2Vec2 m_velocity;
    b2Vec2 m_acceleration;

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
    b2Body* m_pBody;
    b2Fixture* m_pFixture;
};

#endif
