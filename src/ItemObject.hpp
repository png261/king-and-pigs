#ifndef ITEM_OBJECT_H
#define ITEM_OBJECT_H

#include "PlatformerObject.hpp"

class ItemObject : public PlatformerObject
{
public:
    virtual void bonus() = 0;
    std::string type() { return "ItemObject"; }
};
#endif
