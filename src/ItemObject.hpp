#pragma once

#include "GameObject.hpp"

class ItemObject : public GameObject
{
public:
    virtual void bonus() = 0;
    virtual void load(const LoaderParams* const pParams);

protected:
    virtual ~ItemObject(){};
};
