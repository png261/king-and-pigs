#pragma once

#include "GameObject.hpp"

class Decor : public GameObject
{
public:
    virtual void load(const LoaderParams* const pParams);
};
