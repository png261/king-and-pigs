#pragma once

#include "GameObject.hpp"

class Decor : public GameObject
{
public:
    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
};
