#pragma once

#include "ItemObject.hpp"

class Heart final : public ItemObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams);

    void update();
    void bonus();
    void loadAnimation();
};

