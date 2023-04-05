#include "ItemObject.hpp"
#include "PhysicWorld.hpp"

void ItemObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);
    this->setFilterData(PhysicWorld::CAT_ITEM, PhysicWorld::MASK_ITEM);
}
