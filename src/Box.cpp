#include "Box.hpp"

#include "Game.hpp"
#include "PhysicManager.hpp"
#include "SoundManager.hpp"
#include "Utils.hpp"

Box::Box()
    : GameObject()
    , DamageableObject(1, 200, 100)
{}

void Box::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), getWidth(), getHeight());

    setFilterData(ContactCategory::CAT_BOX, ContactMask::MASK_BOX);
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
        /* breakIntoPieces(); */
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

void Box::breakIntoPieces()
{
    auto params = std::make_unique<LoaderParams>(
        LoaderParams(getPosition().x - 10 * 0.5f, getPosition().y - 10 * 0.5f - 20, 10, 10));

    Game::Instance().getLevel()->spawnObject("Box", std::move(params));
    Game::Instance().getLevel()->spawnObject("Box", std::move(params));
    Game::Instance().getLevel()->spawnObject("Box", std::move(params));
    Game::Instance().getLevel()->spawnObject("Box", std::move(params));
}

void Box::randomBonus()
{
    auto params =
        std::make_unique<LoaderParams>(LoaderParams(getPosition().x, getPosition().y, 10, 10));
    if (Utils::isProbable(30)) {
        Game::Instance().getLevel()->spawnObject("Heart", std::move(params));
        return;
    }

    if (Utils::isProbable(10)) {
        Game::Instance().getLevel()->spawnObject("Diamond", std::move(params));
        return;
    }
}
