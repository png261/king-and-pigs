#include "DoorOut.hpp"
#include "Log.hpp"

void DoorOut::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Door::load(std::move(pParams));

    setFilterData(PhysicWorld::CAT_DOOR_OUT, PhysicWorld::MASK_DOOR_OUT);
    open();
}

void DoorOut::update()
{
    Door::update();
    if (isOpened()) {
        close();
    }
}
