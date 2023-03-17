#pragma once

#include "GameObject.hpp"

class ItemObject : public GameObject
{
public:
    virtual void bonus() = 0;
    virtual void load(std::unique_ptr<LoaderParams> const& pParams);

protected:
    virtual ~ItemObject(){};
};
