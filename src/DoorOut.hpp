#pragma once

#include "Door.hpp"

class DoorOut : public Door
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void loadAnimation() override;
};
