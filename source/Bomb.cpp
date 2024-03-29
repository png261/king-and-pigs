#include "Bomb.hpp"

#include "InputManager.hpp"
#include "PhysicManager.hpp"
#include "SoundManager.hpp"

Bomb::Bomb()
    : GameObject()
    , AttackerObject(1, 20, 9999)
    , is_on_(false)
    , on_timer_(1000)
{}

void Bomb::load(const LoaderParams& params)
{
    Object::load(params);
    createBody(params.x(), params.y(), width_, height_);

    createCircleFixture(
        {0, width_ / 4.0f},
        width_ / 2,
        ContactCategory::CAT_BOMB,
        ContactMask::MASK_BOMB);

    createCircleSensor(
        {0, 0},
        attack_range_,
        ContactCategory::CAT_ATTACK_SENSOR,
        ContactMask::MASK_PIG_ATTACK_SENSOR);

    loadAnimation();
}

void Bomb::loadAnimation()
{
    animations_[OFF] = std::make_unique<Animation>("bomb_off", 52, 56);
    animations_[ON] = std::make_unique<Animation>("bomb_on", 52, 56, 4);
    animations_[EXPLODE] = std::make_unique<Animation>("bomb_explode", 52, 56, 6, false);

    current_animation_ = OFF;
    animations_[current_animation_]->start();
}

void Bomb::update()
{
    if (isOn() && current_animation_ == EXPLODE && animations_[current_animation_]->isFinished()) {
        disappear();
        return;
    }

    GameObject::update();
    AttackerObject::update();

    if (InputManager::Instance().isKeyDown(KEY_B)) {
        turnOn();
    }


    if (isOn() && on_timer_.isDone() && current_animation_ != EXPLODE) {
        explode();
    }

    updateAnimaton();
}

void Bomb::turnOn()
{
    SoundManager::Instance().playSFX("bomb_on");
    is_on_ = true;
    on_timer_.start();
    current_animation_ = ON;
    animations_[current_animation_]->start();
}

void Bomb::explode()
{
    SoundManager::Instance().playSFX("bomb_explode");
    attack();
}


void Bomb::updateAnimaton()
{
    if (isAttack()) {
        current_animation_ = EXPLODE;
        animations_[current_animation_]->start();
    }
}

bool Bomb::isOn() const
{
    return is_on_;
}
