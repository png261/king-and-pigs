#pragma once

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
