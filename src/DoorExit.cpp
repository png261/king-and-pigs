#include "DoorExit.hpp"

DoorExit::DoorExit() {}

void DoorExit::load(const LoaderParams& params)
{
    Door::load(params);
    createRectangleSensor(
        {width_ / 4.0f - 5, height_ / 4.0f - 5},
        5,
        5,
        ContactCategory::CAT_DOOR_EXIT,
        ContactMask::MASK_DOOR_EXIT);
}
