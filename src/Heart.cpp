#include "Heart.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"

void Heart::load(std::unique_ptr<LoaderParams> const& params)
{
    ItemObject::load(params);
    body_->SetGravityScale(0);
    fixture_->SetSensor(true);
    loadAnimation();
}

void Heart::loadAnimation()
{
    animations_[NORMAL] = std::make_unique<Animation>("heart_idle", 18, 14, 7);
    animations_[HIT] = std::make_unique<Animation>("heart_hit", 18, 14, 2, false);

    current_animation_ = NORMAL;
    animations_[current_animation_]->start();
}

void Heart::update()
{
    ItemObject::update();
    if (current_animation_ == HIT && animations_[current_animation_]->isFinished()) {
        disappear();
    }
}

void Heart::bonus()
{
    SoundManager::Instance().playSFX("heart_bonus");
    Game::Instance().getLevel()->getPlayer()->heal(1);
    current_animation_ = HIT;
    animations_[current_animation_]->start();
}
