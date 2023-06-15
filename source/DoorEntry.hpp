#pragma once

#include "Door.hpp"
#include "ObjectFactory.hpp"

class DoorEntry final : public Door
{
public:
    void load(const LoaderParams& params) override;
    void update() override;
};

class DoorEntryCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<DoorEntry>(); }
};
