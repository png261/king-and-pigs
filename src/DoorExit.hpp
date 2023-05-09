#pragma once

#include "Door.hpp"
#include "ObjectFactory.hpp"

class DoorExit final : public Door
{
public:
    DoorExit();
    void load(std::unique_ptr<LoaderParams> const& params) override;
};

class DoorExitCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<DoorExit>(); }
};
