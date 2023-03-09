#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

class Enemy : public GameObject
{
public:
    virtual void load(const LoaderParams* const pParams);

protected:
    Enemy()
        : GameObject()
    {}
};
