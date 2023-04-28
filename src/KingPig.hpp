#pragma once

#include "Pig.hpp"

class KingPig final : public Pig
{
public:
    KingPig();
    void loadAnimation() override;

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
};

class KingPigCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<KingPig>(); }
};
