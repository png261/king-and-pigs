#pragma once

#include "PhysicWorld.hpp"

class PhysicObject
{
public:
    PhysicObject();
    virtual ~PhysicObject() = default;
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
    virtual void jump() const;

    virtual void setMoveRight(bool can_move_right);
    virtual void setMoveLeft(bool can_move_left);

    virtual void setFilterData(PhysicWorld::Category category, PhysicWorld::Mask mask) const;

    b2Fixture* createPolygonSensor(
        const b2Vec2& position,
        const int width,
        const int height,
        const PhysicWorld::Category category,
        const PhysicWorld::Mask mask) const;

    b2Fixture* createCircleSensor(
        const b2Vec2& position,
        const int radius,
        const PhysicWorld::Category category,
        const PhysicWorld::Mask mask) const;

protected:
    b2Body* body_;
    b2Fixture* fixture_;

    bool can_move_right_;
    bool can_move_left_;
    bool can_jump_;
    bool is_ground_;
    bool is_running_;
    bool is_disabled_jump_;

    float move_speed_;
    float jump_height_;
    int num_foot_touch_;
};
