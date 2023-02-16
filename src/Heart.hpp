#ifndef HEART_HPP
#define HEART_HPP

#include "PlatformerObject.hpp"

class Heart : public PlatformerObject
{
public:
    Heart();
    virtual ~Heart() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual std::string type() { return "Heart"; }
};

#endif
