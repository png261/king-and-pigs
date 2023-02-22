#ifndef BOX_HPP
#define BOX_HPP

#include "Enemy.hpp"


class Box : public Enemy
{
public:
    Box();
    virtual ~Box() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual std::string type() const { return "Box"; }
};

#endif
