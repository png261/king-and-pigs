#pragma once

#include "Door.hpp"
#include "ObjectFactory.hpp"

class DoorIn final : public Door
{
public:
    DoorIn();
    void load(std::unique_ptr<LoaderParams> const& params) override;
    void createSensor();
};

class DoorInCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<DoorIn>(); }
};
