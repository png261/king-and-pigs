#pragma once

#include "AttackerObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "VisionObject.hpp"

class Player final : public GameObject,
                     public VisionObject,
                     public DamageableObject,
                     public AttackerObject
{
public:
    Player();
    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
    void updateAnimation() override;
    void loadAnimation() override;
    void draw() override;

    bool isWantEnterDoor();
    bool isEnteringDoor();
    void enterDoor();

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
        ENTERING_DOOR,
        LEAVING_DOOR,
    };

    void handleInput();
    void handleSound();
    void handleVision();
    void leavingDoor();

    Timer leavingDoorTimer;
    bool is_entering_door_;
    bool is_want_enter_door_;
};

class PlayerCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<Player>(); }
};
