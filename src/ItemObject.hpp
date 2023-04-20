#pragma once

#include "GameObject.hpp"

class ItemObject : public GameObject
{
public:
    virtual void load(std::unique_ptr<LoaderParams> const& params) override;
    virtual void bonus() = 0;
};
