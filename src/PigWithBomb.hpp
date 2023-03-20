#pragma once

#include "Pig.hpp"

class PigWithBomb : public Pig
{
public:
    PigWithBomb();
    ~PigWithBomb();

    void load(std::unique_ptr<LoaderParams> const& pParams);
    void update();
    void loadAnimation();
    void updateAnimaton();
    void throwBomb();

private:
};
