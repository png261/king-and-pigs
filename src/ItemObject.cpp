#include "ItemObject.hpp"
#include "PhysicWorld.hpp"

void ItemObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    createBody(pParams->x(), pParams->y(), m_width, m_height);
    setFilterData(PhysicWorld::CAT_ITEM, PhysicWorld::MASK_ITEM);
}
