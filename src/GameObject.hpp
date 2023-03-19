#pragma once

#include <memory>
#include "Animation.hpp"
#include "LoaderParams.hpp"
#include "PhysicWorld.hpp"
#include "TextureManager.hpp"

class GameObject
{
public:
    virtual ~GameObject();

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
    virtual void update();
    virtual void draw();
    virtual void loadAnimation();
    virtual void createBody(const int x, const int y, const int width, const int height);

    virtual b2Body* getBody() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual b2Vec2 getPosition() const;
    virtual float getAngle() const;

    virtual bool isUpdating() const;
    virtual bool isExist() const;
    virtual bool isOnGround() const;

    virtual void setUpdating(const bool bUpdating);
    virtual void changeFootContact(const int n);

    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();

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

    bool m_bOnGround;

    std::map<Animation::AnimationID, std::unique_ptr<Animation>> m_animations;
    Animation::AnimationID m_curAnimation;
};
