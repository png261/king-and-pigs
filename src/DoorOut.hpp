#pragma once

#include "Door.hpp"

class DoorOut final : public Door
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
};
