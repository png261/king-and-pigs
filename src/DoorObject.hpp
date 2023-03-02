#ifndef DOOR_OBJECT_HPP
#define DOOR_OBJECT_HPP

#include "PlatformerObject.hpp"

class DoorObject : public PlatformerObject
{
public:
    DoorObject();
    virtual void load(const LoaderParams* const pParams);
    virtual void update();
    virtual std::string type() const;

private:
};

#endif
