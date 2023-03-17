#include "DoorOut.hpp"

void DoorOut::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Door::load(std::move(pParams));

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
