#include "DoorOut.hpp"
#include "Log.hpp"

void DoorOut::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Door::load(std::move(pParams));

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_DOOR_OUT;
    filter.maskBits = PhysicWorld::MASK_DOOR_OUT;
    m_pFixture->SetFilterData(filter);
    this->open();
}

void DoorOut::update()
{
    Door::update();
    if (this->isOpened()) {
        this->close();
    }
}
