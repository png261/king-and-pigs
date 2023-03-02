#ifndef EMENY_HPP
#define EMENY_HPP

#include "Game.hpp"
#include "PlatformerObject.hpp"

class Enemy : public PlatformerObject
{
public:
    virtual std::string type() const { return "Enemy"; }
    virtual void load(const LoaderParams* const pParams);
    virtual void draw();

protected:
    Enemy()
        : PlatformerObject()
    {}
};

#endif
