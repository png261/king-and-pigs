#include "DoorOut.hpp"

void DoorOut::load(const LoaderParams* const pParams)
{
    Door::load(pParams);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_DOOR_OUT;
    filter.maskBits = PhysicWorld::MASK_DOOR_OUT;
    m_pFixture->SetFilterData(filter);
}

void DoorOut::loadAnimation()
{
    Door::loadAnimation();
    m_curAnimation = Animation::DOOR_OPEN;
    m_animations[m_curAnimation]->start();
}
