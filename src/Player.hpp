#pragma once

#include "AttackerObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "ObjectFactory.hpp"
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
    void draw() const override;

    bool isWantEnterDoor() const;
    bool isEnteringDoor() const;
    void enterDoor();

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
        ENTERING_DOOR,
        LEAVING_DOOR,
    };

    void handleInput();
    void handleSound();
    void handleVision();
    void leavingDoor();

    Timer leaving_door_timer_;
    bool is_entering_door_;
    bool is_want_enter_door_;
};

class PlayerCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Player>(); }
};
