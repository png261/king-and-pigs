#pragma once

#include "Pig.hpp"

class PigWithBomb : public Pig
{
public:
    PigWithBomb();
    ~PigWithBomb();

    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void loadAnimation() override;

    void becomeNormal();
    void throwBomb();

private:
    bool m_bThrowing;
};