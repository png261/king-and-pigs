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

void PigWithBomb::load(const LoaderParams& params)
{
    Pig::load(params);
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
    const int bomb_size = 7;
    LoaderParams params(
        getX() - width_ * 0.5f,
        getY() - height_ * 0.5f - bomb_size,
        bomb_size,
        bomb_size);

    auto bomb = dynamic_cast<Bomb*>(Game::Instance().getLevel()->spawnObject("Bomb", params));
    bomb->getBody()->ApplyForce(
        b2Vec2(direction_ * 7, -7),
        bomb->getBody()->GetWorldCenter(),
        true);
    bomb->turnOn();
}

void PigWithBomb::becomeNormal()
{
    const int pig_size = 20;
    disappear();
    LoaderParams params(getX() - (pig_size * 0.5f), getY() - (pig_size * 0.5f), pig_size, pig_size);
    Game::Instance().getLevel()->spawnObject("Pig", params);
}
