#include "Box.hpp"
#include <iostream>

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
    std::cout << "box collision" << std::endl;
}
void Box::clean() {}
