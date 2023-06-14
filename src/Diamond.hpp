#pragma once

#include "ItemObject.hpp"
#include "ObjectFactory.hpp"

class Diamond final : public ItemObject
{
public:
    void load(const LoaderParams& params) override;
    void update() override;
    void bonus() override;
    void loadAnimation() override;

private:
    enum AnimationID { NORMAL, HIT };
};

class DiamondCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Diamond>(); }
};
