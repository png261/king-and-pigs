#ifndef EMENY_HPP
#define EMENY_HPP

#include "Game.hpp"
#include "GameObject.hpp"

class Enemy : public GameObject
{
public:
    virtual void load(const LoaderParams* const pParams);
    virtual void draw();

protected:
    Enemy()
        : GameObject()
    {}
};

#endif
