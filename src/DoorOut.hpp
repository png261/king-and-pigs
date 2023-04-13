#pragma once

#include "Door.hpp"
#include "GameObjectFactory.hpp"

class DoorOut final : public Door
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
};

class DoorOutCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<DoorOut>(); }
};
