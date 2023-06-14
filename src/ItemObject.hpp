#pragma once

#include "GameObject.hpp"

class ItemObject : public GameObject
{
public:
    virtual void load(const LoaderParams& params) override;
    virtual void bonus() = 0;
};
