#pragma once

#include "AttackerObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
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
    virtual void handleMovement();
    virtual void changeDirection();

    virtual void seeingBox();
    virtual void seeingPig();
    virtual void seeingPlayer();
    virtual void seeingWall();
};
