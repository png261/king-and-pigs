#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "Box2D.hpp"
#include "LoaderParams.hpp"
#include "TextureManager.hpp"

class GameObject
{
public:
    virtual ~GameObject();

    virtual void load(const LoaderParams* pParams);
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual std::string type() const = 0;

    b2Vec2& getPosition();

    int getWidth() const;
    int getHeight() const;
    b2Body* getBody() const;

    bool isUpdating() const;
    bool isDead() const;

    void setUpdating(bool updating);

protected:
    GameObject();

    // movement
    b2Vec2 m_position;

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
