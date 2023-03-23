#pragma once

#include "ItemObject.hpp"

class Heart final : public ItemObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void bonus() override;
    void loadAnimation() override;
};
