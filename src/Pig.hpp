#pragma once

#include "AttackerObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "VisionObject.hpp"

class Pig : public GameObject, public VisionObject, public DamageableObject, public AttackerObject
{
public:
    Pig();
    virtual void load(std::unique_ptr<LoaderParams> const& pParams) override;
    virtual void loadAnimation() override;
    virtual void update() override;
    virtual void updateAnimation() override;
    virtual void draw() override;

private:
    enum animations {
        IDLE,
        RUN,
        JUMP,
        FALL,
        GROUND,
        ATTACK,
        DYING,
        HIT,
    };

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
    std::unique_ptr<GameObject> create() const { return std::make_unique<Pig>(); }
};
