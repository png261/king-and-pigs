#ifndef HEART_H
#define HEART_H

#include "PlatformerObject.h"

class Heart : public PlatformerObject
{
public:
    Heart();
    virtual ~Heart() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void collision();

    virtual std::string type() { return "Box"; }
};

#endif
