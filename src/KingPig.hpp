#pragma once

#include "Pig.hpp"

class KingPig : public Pig
{
public:
    KingPig();
    virtual void loadAnimation() override;

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
