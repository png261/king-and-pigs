#pragma once

#include "Object.hpp"
#include "PhysicManager.hpp"

class PhysicObject : public Object
{
public:
    PhysicObject();
    virtual ~PhysicObject() = default;
    virtual void update() override;

    virtual b2Body* getBody() const;

    virtual b2Vec2 getPosition() const override;

    virtual float getAngle() const;
    virtual int getFootContact() const;
    virtual bool isOnGround() const;
    virtual bool isRunning() const;
    virtual bool canMoveRight() const;
    virtual bool canMoveLeft() const;
    virtual bool canJump() const;
    virtual bool isDisableJump() const;

    virtual void changeFootContact(const int n);

    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump() const;

    virtual void setMoveRight(const bool can_move_right);
    virtual void setMoveLeft(const bool can_move_left);

    virtual void setFilterData(const ContactCategory category, const ContactMask mask) const;

    virtual void createBody(const int x, const int y, const int width, const int height);

    virtual void createRectangleFixture(
        const b2Vec2& position,
        const int width,
        const int height,
        const ContactCategory category,
        const ContactMask mask);

    virtual void createCircleFixture(
        const b2Vec2& position,
        const int radius,
        const ContactCategory category,
        const ContactMask mask);

    virtual b2Fixture* createRectangleSensor(
        const b2Vec2& position,
        const int width,
        const int height,
        const ContactCategory category,
        const ContactMask mask) const;

    virtual b2Fixture* createCircleSensor(
        const b2Vec2& position,
        const int radius,
        const ContactCategory category,
        const ContactMask mask) const;

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
