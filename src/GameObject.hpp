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

    b2Vec2 getPosition();
    float getAngle();
    int getWidth() const;
    int getHeight() const;

    b2Body* getBody() const;

    bool isUpdating() const;
    bool isExist() const;

    void setUpdating(const bool updating);
    virtual void changeFootContact(int n);

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

    double m_angle;
    bool m_bFlipped;

    std::map<Animation::AnimationID, Animation*> m_animations;
    Animation::AnimationID m_curAnimation;

    bool m_bExist;

    b2Body* m_pBody;
    b2Fixture* m_pFootSensor;
    b2Fixture* m_pFixture;

    ObjectPosition m_currentState;
    ObjectState m_currentAttackState;

    float m_moveSpeed;
    float m_jumpHeight;

    int m_footContact;
};
