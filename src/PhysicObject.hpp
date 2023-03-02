#ifndef PHYSIC_OBJECT_HPP
#define PHYSIC_OBJECT_HPP

#include "LoaderParams.hpp"

class PhysicObject
{
public:
    virtual void update();
    virtual void load(const LoaderParams* const pParams);

private:
};

#endif
