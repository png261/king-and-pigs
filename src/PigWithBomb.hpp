#pragma once

#include "Pig.hpp"

class PigWithBomb : public Pig
{
public:
    PigWithBomb();

    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void loadAnimation() override;

    void becomeNormal();
    void throwBomb();

private:
    enum animations { IDLE, RUN, THROWING };
    bool m_bThrowing;
};

class PigWithBombCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<PigWithBomb>(); }
};
