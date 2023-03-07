#pragma once

#include "ItemObject.hpp"

class Heart final : public ItemObject
{
public:
    void load(const LoaderParams* const pParams);

    void update();
    void bonus();
    void loadAnimation();
};

