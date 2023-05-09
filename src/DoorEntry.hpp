#pragma once

#include "Door.hpp"
#include "ObjectFactory.hpp"

class DoorEntry final : public Door
{
public:
    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
};

class DoorEntryCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<DoorEntry>(); }
};
