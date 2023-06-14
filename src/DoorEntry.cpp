#include "DoorEntry.hpp"

void DoorEntry::load(const LoaderParams& params)
{
    Door::load(params);
    open();
}

void DoorEntry::update()
{
    Door::update();
    if (isOpened()) {
        close();
    }
}
