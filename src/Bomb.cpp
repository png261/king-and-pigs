#include "Bomb.hpp"

#include "InputHandler.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"
#include "Utils.hpp"

Bomb::Bomb()
    : GameObject()
    , AttackerObject(1, 20, 9999)
    , is_on_(false)
    , on_timer_(1000)
{}

void Bomb::load(std::unique_ptr<LoaderParams> const& params)
{
    Object::load(std::move(params));

    PhysicWorld::Instance().createCircleBody(
        body_,
        b2Vec2(params->x(), params->y()) + 0.5f * b2Vec2(width_, height_),
        width_,
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

    if (isOn() && on_timer_.isDone()) {
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
