#include "ItemObject.hpp"

#include "PhysicManager.hpp"

void ItemObject::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), width_, height_);
    setFilterData(ContactCategory::CAT_ITEM, ContactMask::MASK_ITEM);
}
