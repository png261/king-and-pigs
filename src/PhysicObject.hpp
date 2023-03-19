#pragma once
#include "PhysicWorld.hpp"

class PhysicObject
{
public:
    PhysicObject();
    ~PhysicObject();

    virtual void update();

    virtual void createBody(const int x, const int y, const int width, const int height);
    virtual void changeFootContact(const int n);
    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();

    virtual b2Body* getBody() const;
    virtual b2Vec2 getPosition() const;
    virtual float getAngle() const;
    virtual int getFootContact() const;
    virtual bool isOnGround() const;

protected:
    b2Body* m_pBody;
    b2Fixture* m_pFixture;

    bool m_bOnGround;

    float m_moveSpeed;
    float m_jumpHeight;
    int m_footContact;
};
