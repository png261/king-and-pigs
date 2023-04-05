#include "DoorOut.hpp"
#include "Log.hpp"

void DoorOut::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Door::load(std::move(pParams));

    this->setFilterData(PhysicWorld::CAT_DOOR_OUT, PhysicWorld::MASK_DOOR_OUT);
    this->open();
}

void DoorOut::update()
{
    Door::update();
    if (this->isOpened()) {
        this->close();
    }
}
