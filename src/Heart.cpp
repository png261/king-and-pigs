#include "Heart.h"
#include <iostream>

Heart::Heart()
    : PlatformerObject()
{}

void Heart::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);
}

void Heart::update()
{
    PlatformerObject::update();
}
void Heart::draw()
{
    PlatformerObject::draw();
}
void Heart::collision()
{
    m_textureID = "heart dead";
    m_numFrames = 2;
}
void Heart::clean() {}
