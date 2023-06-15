#include "Box.hpp"

#include "Game.hpp"
#include "PhysicManager.hpp"
#include "SoundManager.hpp"
#include "Utils.hpp"

Box::Box()
    : GameObject()
    , DamageableObject(1, 200, 100)
{}

void Box::load(const LoaderParams& params)
{
    GameObject::load(params);
    createBody(params.x(), params.y(), getWidth(), getHeight());

    createRectangleFixture(
        {0, 0},
        getWidth(),
        getHeight(),
        ContactCategory::CAT_BOX,
        ContactMask::MASK_BOX);

    body_->SetFixedRotation(false);

    loadAnimation();
}

void Box::loadAnimation()
{
    animations_[NORMAL] = std::make_unique<Animation>("box_idle", 22, 16, 1);
    animations_[HIT] = std::make_unique<Animation>("box_hit", 22, 16, 2);

    current_animation_ = NORMAL;
    animations_[current_animation_]->start();
}

void Box::update()
{
    if (isDead()) {
        randomBonus();
        SoundManager::Instance().playSFX("box_broken");
        disappear();
        return;
    }

    GameObject::update();
    DamageableObject::update();
    updateAnimation();
}

void Box::updateAnimation()
{
    int new_animation = current_animation_;

    if (isDying()) {
        new_animation = HIT;
    } else {
        new_animation = NORMAL;
    }

    if (new_animation != current_animation_) {
        animations_[current_animation_]->stop();
        current_animation_ = new_animation;
        animations_[current_animation_]->start();
    }
}

void Box::randomBonus()
{
    LoaderParams params(getX(), getY(), 10, 10);
    if (Utils::isProbable(30)) {
        Game::Instance().getLevel()->spawnObject("Heart", params);
        return;
    }

    if (Utils::isProbable(10)) {
        Game::Instance().getLevel()->spawnObject("Diamond", params);
        return;
    }
}
