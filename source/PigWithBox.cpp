#include "PigWithBox.hpp"

#include "Box.hpp"
#include "Game.hpp"

PigWithBox::PigWithBox()
    : Pig()
    , is_throwing_(false)
{
    is_disabled_jump_ = true;
}

void PigWithBox::loadAnimation()
{
    Pig::loadAnimation();

    animations_[IDLE] = std::make_unique<Animation>("pigWithBox_idle", 26, 30, 9);
    animations_[RUN] = std::make_unique<Animation>("pigWithBox_run", 26, 30, 6);
    animations_[THROWING] = std::make_unique<Animation>("pigWithBox_throwing", 26, 30, 5);

    current_animation_ = IDLE;
    animations_[current_animation_]->start();
}

void PigWithBox::update()
{
    if (isInvulnerable()) {
        becomeNormal();
        disappear();
        return;
    }
    Pig::update();
    if (isSeeing(ContactCategory::CAT_PLAYER) && vision_nearest_distance_ <= 100) {
        throwBox();
        becomeNormal();
    }
}

void PigWithBox::throwBox()
{
    LoaderParams params(getX() - width_ * 0.5f, getY() - height_ * 0.5f - 20, 20, 20);

    auto box = dynamic_cast<Box*>(Game::Instance().getLevel()->spawnObject("Box", params));
    box->getBody()->ApplyForce(
        b2Vec2(direction_ * 100, -32),
        box->getBody()->GetWorldCenter(),
        true);
}

void PigWithBox::becomeNormal()
{
    const int pig_size = 20;
    disappear();
    LoaderParams params(getX() - (pig_size * 0.5f), getY() - (pig_size * 0.5f), pig_size, pig_size);
    Game::Instance().getLevel()->spawnObject("Pig", params);
}
