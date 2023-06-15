#include "Door.hpp"

#include "SoundManager.hpp"

Door::Door()
    : GameObject()
    , is_opened_(false)
{}

void Door::load(const LoaderParams& params)
{
    GameObject::load(params);
    createBody(params.x(), params.y(), width_, height_);

    createRectangleSensor(
        {0, 0},
        width_,
        height_,
        ContactCategory::CAT_NONE,
        ContactMask::MASK_NONE);

    loadAnimation();
}

void Door::loadAnimation()
{
    animations_[DOOR_CLOSED] = std::make_unique<Animation>("door_idle", 46, 56, 1);
    animations_[DOOR_OPENING] = std::make_unique<Animation>("door_open", 46, 56, 5, false);
    animations_[DOOR_CLOSING] = std::make_unique<Animation>("door_close", 46, 56, 3, false);

    current_animation_ = DOOR_CLOSED;
    animations_[current_animation_]->start();
}

void Door::update()
{
    GameObject::update();
    if (isOpened() && current_animation_ == DOOR_CLOSING &&
        animations_[DOOR_CLOSING]->isFinished()) {
        SoundManager::Instance().playSFX("door_close");
        is_opened_ = false;
    }

    if (isClosed() && current_animation_ == DOOR_OPENING &&
        animations_[DOOR_OPENING]->isFinished()) {
        SoundManager::Instance().playSFX("door_open");
        is_opened_ = true;
    }
}

void Door::open()
{
    if (isOpened()) {
        return;
    }

    current_animation_ = DOOR_OPENING;
    animations_[current_animation_]->start();
}

void Door::close()
{
    if (isClosed()) {
        return;
    }

    current_animation_ = DOOR_CLOSING;
    animations_[current_animation_]->start();
}

bool Door::isOpened() const
{
    return is_opened_;
}

bool Door::isClosed() const
{
    return !is_opened_;
}
