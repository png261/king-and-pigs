#include "ItemObject.hpp"
#include "PhysicWorld.hpp"

void ItemObject::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ITEM;
    filter.maskBits = PhysicWorld::MASK_ITEM;
    m_pFixture->SetFilterData(filter);
}
