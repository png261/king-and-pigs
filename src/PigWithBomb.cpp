#include "PigWithBomb.hpp"

#include "Bomb.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputManager.hpp"

PigWithBomb::PigWithBomb()
    : Pig()
    , is_throwing_(false)
{
    is_disabled_jump_ = true;
}

void PigWithBomb::load(std::unique_ptr<LoaderParams> const& params)
{
    Pig::load(std::move(params));
    loadAnimation();
}
void PigWithBomb::loadAnimation()
{
    Pig::loadAnimation();

    animations_[IDLE] = std::make_unique<Animation>("pigWithBomb_idle", 26, 26, 10);
    animations_[RUN] = std::make_unique<Animation>("pigWithBomb_run", 26, 26, 6);
    animations_[THROWING] = std::make_unique<Animation>("pigWithBomb_throwing", 26, 26, 5);

    current_animation_ = IDLE;
    animations_[current_animation_]->start();
}

void PigWithBomb::update()
{
    Pig::update();
    if (isSeeing(ContactCategory::CAT_PLAYER) && vision_nearest_distance_ <= 100) {
        throwBomb();
        becomeNormal();
    }
}

void PigWithBomb::throwBomb()
{
    auto params = std::make_unique<LoaderParams>(
        LoaderParams(getPosition().x - width_ * 0.5f, getPosition().y - height_ * 0.5f - 10, 7, 7));

    auto bomb =
        dynamic_cast<Bomb*>(Game::Instance().getLevel()->spawnObject("Bomb", std::move(params)));
    bomb->getBody()->ApplyForce(
        b2Vec2(direction_ * 50, -32),
        bomb->getBody()->GetWorldCenter(),
        true);
    bomb->turnOn();
}

void PigWithBomb::becomeNormal()
{
    disappear();
    auto params2 = std::make_unique<LoaderParams>(
        LoaderParams(getPosition().x - (20 * 0.5f), getPosition().y - (20 * 0.5f), 20, 20));
    Game::Instance().getLevel()->spawnObject("Pig", std::move(params2));
}
