#pragma once

#include "Door.hpp"

class DoorIn : public Door
{
public:
    DoorIn();
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void createSensor();
};
