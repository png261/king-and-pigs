#pragma once

#include "Door.hpp"

class DoorIn : public Door
{
public:
    void load(const LoaderParams* const pParams);
    void createSensor();
    void open();
};
