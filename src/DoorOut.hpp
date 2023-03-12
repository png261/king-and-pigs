#pragma once

#include "Door.hpp"

class DoorOut : public Door
{
public:
    void load(const LoaderParams* const pParams);
    void loadAnimation();
};
