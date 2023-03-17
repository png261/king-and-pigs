#include "ItemObject.hpp"
#include "PhysicWorld.hpp"

void ItemObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ITEM;
    filter.maskBits = PhysicWorld::MASK_ITEM;
    m_pFixture->SetFilterData(filter);
}
