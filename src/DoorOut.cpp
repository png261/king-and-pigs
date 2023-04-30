#include "DoorOut.hpp"

void DoorOut::load(std::unique_ptr<LoaderParams> const& params)
{
    Door::load(std::move(params));

    setFilterData(ContactCategory::CAT_DOOR_OUT, ContactMask::MASK_DOOR_OUT);
    open();
}

void DoorOut::update()
{
    Door::update();
    if (isOpened()) {
        close();
    }
}
