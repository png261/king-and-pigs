#pragma once

#include "Pig.hpp"

class PigWithBomb final : public Pig
{
public:
    PigWithBomb();

    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
    void loadAnimation() override;

    void becomeNormal();
    void throwBomb();

private:
    enum AnimationID { IDLE, RUN, THROWING };
    bool is_throwing_;
};

class PigWithBombCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<PigWithBomb>(); }
};
