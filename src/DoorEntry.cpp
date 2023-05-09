#include "DoorEntry.hpp"

void DoorEntry::load(std::unique_ptr<LoaderParams> const& params)
{
    Door::load(std::move(params));
    setFilterData(ContactCategory::CAT_DOOR_ENTRY, ContactMask::MASK_DOOR_ENTRY);
    open();
}

void DoorEntry::update()
{
    Door::update();
    if (isOpened()) {
        close();
    }
}
