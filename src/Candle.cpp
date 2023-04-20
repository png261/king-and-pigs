#include "Candle.hpp"

void Candle::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), width_, height_);

    body_->SetGravityScale(0);

    setFilterData(PhysicWorld::CAT_NONE, PhysicWorld::MASK_NONE);
    loadAnimation();
};

void Candle::loadAnimation()
{
    animations_[NORMAL] = std::make_unique<Animation>("candle_idle", 14, 32, 8);
    current_animation_ = NORMAL;
    animations_[current_animation_]->start();
}
