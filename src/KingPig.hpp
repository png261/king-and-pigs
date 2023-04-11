#pragma once

#include "Pig.hpp"

class KingPig final : public Pig
{
public:
    KingPig();
    void loadAnimation() override;

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
};
