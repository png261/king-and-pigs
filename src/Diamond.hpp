#pragma once

#include "GameObjectFactory.hpp"
#include "ItemObject.hpp"

class Diamond final : public ItemObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void bonus() override;
    void loadAnimation() override;

private:
    enum animations { NORMAL, HIT };
};

class DiamondCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<Diamond>(); }
};
