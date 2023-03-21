#pragma once

#include "ItemObject.hpp"

class Heart final : public ItemObject
{
public:
    void bonus() override;
    void loadAnimation() override;
};
