#include "GameObject.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

GameObject::GameObject()
    : PhysicObject()
    , width_(0)
    , height_(0)
    , is_exist_(true)
    , is_flipped_(false)
    , direction_(RIGHT)
{}

void GameObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
    width_ = pParams->width();
    height_ = pParams->height();
}

void GameObject::loadAnimation(){};

void GameObject::draw()
{
    b2Vec2 halfSize = 0.5 * b2Vec2(
                                animations_[current_animation_]->getWidth(),
                                animations_[current_animation_]->getHeight());

    animations_[current_animation_]->draw(
        getPosition() - halfSize - Camera::Instance().getPosition(),
        getAngle(),
        is_flipped_,
        Camera::Instance().getZoom());
}

void GameObject::update()
{
    PhysicObject::update();
    animations_[current_animation_]->update();
}

void GameObject::updateAnimation() {}

bool GameObject::isExist() const
{
    return is_exist_;
}

void GameObject::disappear()
{
    is_exist_ = false;
}

int GameObject::getWidth() const
{
    return width_;
}

int GameObject::getHeight() const
{
    return height_;
}
