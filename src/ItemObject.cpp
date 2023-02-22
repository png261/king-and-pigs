#include "ItemObject.hpp"
#include "Box2D.hpp"
#include "PlatformerObject.hpp"

void ItemObject::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_ITEM;
    filter.maskBits = Box2D::MASK_ITEM;
    m_pFixture->SetFilterData(filter);
}
