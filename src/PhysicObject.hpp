#pragma once
#include "PhysicWorld.hpp"

class PhysicObject
{
public:
    PhysicObject();
    virtual ~PhysicObject();
    virtual void update();

    virtual b2Body* getBody() const;
    virtual b2Vec2 getPosition() const;
    virtual float getAngle() const;
    virtual int getFootContact() const;
    virtual bool isOnGround() const;
    virtual bool isRunning() const;
    virtual bool canMoveRight() const;
    virtual bool canMoveLeft() const;
    virtual bool canJump() const;
    virtual bool isDisableJump() const;

    virtual void createBody(const int x, const int y, const int width, const int height);
    virtual void changeFootContact(const int n);

    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();

    virtual void setMoveRight(bool bMoveRight);
    virtual void setMoveLeft(bool bMoveLeft);

    virtual void setFilterData(PhysicWorld::Category category, PhysicWorld::Mask mask);

protected:
    b2Body* m_pBody;
    b2Fixture* m_pFixture;

    bool m_bCanMoveRight;
    bool m_bCanMoveLeft;
    bool m_bCanJump;
    bool m_bOnGround;
    bool m_bRunning;
    bool m_bDisableJump;

    float m_moveSpeed;
    float m_jumpHeight;
    int m_footContact;
};
