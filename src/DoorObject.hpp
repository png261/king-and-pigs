#ifndef DOOR_OBJECT_HPP
#define DOOR_OBJECT_HPP

#include "GameObject.hpp"

class DoorObject : public GameObject
{
public:
    DoorObject();
    virtual void load(const LoaderParams* const pParams);
    virtual void update();

private:
};

#endif
