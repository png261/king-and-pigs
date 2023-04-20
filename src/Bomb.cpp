#include "Bomb.hpp"

#include "InputHandler.hpp"
#include "Log.hpp"
#include "SoundManager.hpp"

Bomb::Bomb()
    : GameObject()
    , AttackerObject(1, 20, 9999)
    , is_on_(false)
{}

void Bomb::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PhysicWorld::pixelToMeter(
        b2Vec2(params->x(), params->y()) + 0.5f * b2Vec2(width_, height_));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body_ = PhysicWorld::Instance().getWorld()->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = PhysicWorld::pixelToMeter(width_);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = PhysicWorld::CAT_BOMB;
    fixtureDef.filter.maskBits = PhysicWorld::MASK_BOMB;
    fixture_ = body_->CreateFixture(&fixtureDef);

    createCircleSensor(
        {0, 0},
        attack_range_,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    loadAnimation();
    on_timer_.setTime(1000);
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
