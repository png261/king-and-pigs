#pragma once

#include "Pig.hpp"

class PigWithBox : public Pig
{
public:
    PigWithBox();

    void update() override;
    void loadAnimation() override;

    void becomeNormal();
    void throwBox();

private:
    enum AnimationID { IDLE, RUN, THROWING };
    bool is_throwing_;
};

class PigWithBoxCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<PigWithBox>(); }
};
