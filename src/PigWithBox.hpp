#pragma once

#include "Pig.hpp"

class PigWithBox : public Pig
{
public:
    PigWithBox();
    ~PigWithBox();

    void update() override;
    void loadAnimation() override;

    void becomeNormal();
    void throwBox();

private:
    enum animations { IDLE, RUN, THROWING };
    bool m_bThrowing;
};
