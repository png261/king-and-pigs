#include "ItemObject.hpp"
#include "PhysicWorld.hpp"

void ItemObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_ITEM;
    filter.maskBits = PhysicWorld::MASK_ITEM;
    m_pFixture->SetFilterData(filter);
}
