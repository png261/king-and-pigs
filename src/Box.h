#ifndef BOX_H
#define BOX_H

#include "PlatformerObject.h"


class Box : public PlatformerObject
{
public:
    Box();
    virtual ~Box() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void collision();

    virtual std::string type() { return "Box"; }
};

#endif
