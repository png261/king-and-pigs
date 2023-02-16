#include "Box.hpp"

Box::Box()
    : PlatformerObject()
{}

void Box::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);
}

void Box::update()
{
    PlatformerObject::update();
}
void Box::draw()
{
    PlatformerObject::draw();
}
void Box::collision()
{
}
void Box::clean() {}
