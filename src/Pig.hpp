#pragma once

#include "AttackerObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "ObjectFactory.hpp"
#include "VisionObject.hpp"

class Pig : public GameObject, public VisionObject, public DamageableObject, public AttackerObject
{
public:
    Pig();
    virtual void load(const LoaderParams& params) override;
    virtual void loadAnimation() override;
    virtual void update() override;
    virtual void updateAnimation() override;
    virtual void draw() const override;

private:
    enum AnimationID {
        IDLE,
        RUN,
        JUMP,
        FALL,
        GROUND,
        ATTACK,
        DYING,
        HIT,
    };

    virtual void drawHealthBar() const;

    virtual void handleSound();

    virtual void handleMovement();
    virtual void changeDirection();

    virtual void seeingBox();
    virtual void seeingPig();
    virtual void seeingPlayer();
    virtual void seeingWall();
};

class PigCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Pig>(); }
};
