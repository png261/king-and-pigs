#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

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

    b2Vec2& getPosition();
    int getWidth() const;
    int getHeight() const;

    b2Body* getBody() const;

    bool isUpdating() const;
    bool isExist() const;

    void setUpdating(const bool updating);
    virtual void changeFootContact(int n);

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

    b2Vec2 m_position;

    int m_width;
    int m_height;

    int m_textureHeight;
    int m_textureWidth;
    int m_textureX;
    int m_textureY;

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

    int m_moveSpeed;
    int m_jumpSpeed;

    int m_footContact;
};

#endif
