#ifndef ITEM_OBJECT_H
#define ITEM_OBJECT_H

#include "PlatformerObject.hpp"

class ItemObject : public PlatformerObject
{
public:
    virtual void bonus() = 0;
    virtual void load(const LoaderParams* pParams);
    std::string type() const { return "ItemObject"; }
};
#endif
