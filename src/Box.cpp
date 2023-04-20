#include "Box.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"
#include "Utils.hpp"

Box::Box()
    : GameObject()
    , DamageableObject(1, 200, 100)
{}

void Box::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), width_, height_);

    setFilterData(PhysicWorld::CAT_BOX, PhysicWorld::MASK_BOX);
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
    int newAnimation = current_animation_;

    if (isDying()) {
        newAnimation = HIT;
    } else {
        newAnimation = NORMAL;
    }

    if (newAnimation != current_animation_) {
        animations_[current_animation_]->stop();
        current_animation_ = newAnimation;
        animations_[current_animation_]->start();
    }
}

void Box::breakIntoPieces()
{
    auto params = std::make_unique<LoaderParams>(
        LoaderParams(getPosition().x - 10 / 2.0f, getPosition().y - 10 / 2.0f - 20, 10, 10));

    Game::Instance().getLevel()->spawnGameObject("Box", std::move(params));
    Game::Instance().getLevel()->spawnGameObject("Box", std::move(params));
    Game::Instance().getLevel()->spawnGameObject("Box", std::move(params));
    Game::Instance().getLevel()->spawnGameObject("Box", std::move(params));
}

void Box::randomBonus()
{
    auto params =
        std::make_unique<LoaderParams>(LoaderParams(getPosition().x, getPosition().y, 10, 10));
    if (Utils::isProbable(30)) {
        Game::Instance().getLevel()->spawnGameObject("Heart", std::move(params));
        return;
    }

    if (Utils::isProbable(10)) {
        Game::Instance().getLevel()->spawnGameObject("Diamond", std::move(params));
        return;
    }
}
