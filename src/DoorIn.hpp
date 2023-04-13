#pragma once

#include "Door.hpp"
#include "GameObjectFactory.hpp"

class DoorIn final : public Door
{
public:
    DoorIn();
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void createSensor();
};

class DoorInCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<DoorIn>(); }
};
