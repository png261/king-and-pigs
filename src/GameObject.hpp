#pragma once

#include "Animation.hpp"
#include "Box2D.hpp"
#include "LoaderParams.hpp"
#include "TextureManager.hpp"

class GameObject
{
public:
    virtual ~GameObject();

    virtual void load(const LoaderParams* const pParams);
    virtual void update();
    virtual void draw();
    virtual void loadAnimation(){};
    virtual void createBody(const int x, const int y, const int width, const int height);

    virtual b2Body* getBody() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual b2Vec2 getPosition() const;
    virtual float getAngle() const;

    virtual bool isUpdating() const;
    virtual bool isExist() const;

    virtual void setUpdating(const bool updating);
    virtual void changeFootContact(const int n);

    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();

    enum ObjectPosition {
        ON_GROUND,
        ON_FLY,
    };

    enum ObjectState {
        ON_NORMAL,
        ON_HIT,
        ON_ATTACK,
        ON_DIE,
    };

protected:
    GameObject();

    int m_width;
    int m_height;

    bool m_bUpdating;
    bool m_bFlipped;
    bool m_bExist;

    b2Body* m_pBody;
    b2Fixture* m_pFixture;
    float m_moveSpeed;
    float m_jumpHeight;

    int m_footContact;

    ObjectPosition m_currentState;
    ObjectState m_currentAttackState;
    std::map<Animation::AnimationID, Animation*> m_animations;
    Animation::AnimationID m_curAnimation;
};
