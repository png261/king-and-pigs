#ifndef EMENY_HPP
#define EMENY_HPP

#include "Game.hpp"
#include "PlatformerObject.hpp"

class Enemy : public PlatformerObject
{
public:
    virtual std::string type() { return "Enemy"; }
    virtual void load(const LoaderParams* pParams) { PlatformerObject::load(pParams); };
    virtual void draw() { PlatformerObject::draw(); }

protected:
    Enemy()
        : PlatformerObject()
    {}
};

#endif
