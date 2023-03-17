#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

class Enemy : public GameObject
{
public:
    virtual void load(std::unique_ptr<LoaderParams> const& pParams);

protected:
    Enemy()
        : GameObject()
    {}
};
