#include "GameObject.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "PhysicManager.hpp"

GameObject::GameObject()
    : PhysicObject()
    , is_flip_(false)
    , direction_(RIGHT)
{}

void GameObject::loadAnimation(){};

void GameObject::draw() const
{
    const b2Vec2 halfSize = 0.5 * b2Vec2(
                                      animations_.at(current_animation_)->getWidth(),
                                      animations_.at(current_animation_)->getHeight());

    animations_.at(current_animation_)
        ->draw(
            getPosition() - halfSize - Camera::Instance().getPosition(),
            getAngle(),
            is_flip_,
            Camera::Instance().getZoom());
}

void GameObject::update()
{
    PhysicObject::update();
    animations_[current_animation_]->update();
}

void GameObject::updateAnimation() {}
