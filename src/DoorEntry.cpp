#include "DoorEntry.hpp"

void DoorEntry::load(std::unique_ptr<LoaderParams> const& params)
{
    Door::load(std::move(params));
    open();
}

void DoorEntry::update()
{
    Door::update();
    if (isOpened()) {
        close();
    }
}
