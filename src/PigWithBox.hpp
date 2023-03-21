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
    bool m_bThrowing;
};
