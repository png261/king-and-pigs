#include "ItemObject.hpp"

#include "PhysicManager.hpp"

void ItemObject::load(const LoaderParams& params)
{
    GameObject::load(params);
    createBody(params.x(), params.y(), width_, height_);

    createRectangleSensor(
        {0, 0},
        width_,
        height_,
        ContactCategory::CAT_ITEM,
        ContactMask::MASK_ITEM);
}
