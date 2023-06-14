#include "Diamond.hpp"

#include "Game.hpp"
#include "PhysicManager.hpp"
#include "SoundManager.hpp"

void Diamond::load(const LoaderParams& params)
{
    ItemObject::load(params);
    loadAnimation();
}

void Diamond::loadAnimation()
{
    animations_[NORMAL] = std::make_unique<Animation>("diamond_idle", 18, 14, 7);
    animations_[HIT] = std::make_unique<Animation>("diamond_hit", 18, 14, 2, false);

    current_animation_ = NORMAL;
    animations_[current_animation_]->start();
}

void Diamond::update()
{
    ItemObject::update();
    if (current_animation_ == HIT && animations_[current_animation_]->isFinished()) {
        disappear();
    }
}

void Diamond::bonus()
{
    SoundManager::Instance().playSFX("diamond_bonus");
    Game::Instance().addDiamond(+1);
    current_animation_ = HIT;
    animations_[current_animation_]->start();
}
