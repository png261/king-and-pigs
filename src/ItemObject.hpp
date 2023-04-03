#pragma once

#include "GameObject.hpp"

class ItemObject : public GameObject
{
public:
    virtual void load(std::unique_ptr<LoaderParams> const& pParams) override;
    virtual void bonus() = 0;

protected:
    virtual ~ItemObject() = default;
};
