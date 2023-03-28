#pragma once

#include "AttackerObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "VisionObject.hpp"

class Player final : public GameObject,
                     public VisionObject,
                     public DamageableObject,
                     public AttackerObject
{
public:
    Player();
    ~Player();
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void updateAnimation() override;
    void loadAnimation() override;
    void draw() override;

    bool isWantDoorIn();
    bool isDoorIn();
    void doorIn();

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
        DOOR_IN,
        DOOR_OUT,
    };

    void handleInput();
    void doorOut();

    Timer doorOutTimer;
    bool m_bDoorIn;
    bool m_bWantDoorIn;
};
