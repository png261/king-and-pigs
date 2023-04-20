#include "Camera.hpp"

#include "Game.hpp"

Camera::Camera()
    : target_(nullptr)
    , position_(0, 0)
    , zoom_(1)
{}

Camera& Camera::Instance()
{
    static Camera instance{};
    return instance;
}

float Camera::getZoom() const
{
    return zoom_;
}

b2Vec2 Camera::getPosition() const
{
    if (target_ == nullptr) {
        return position_;
    }

    b2Vec2 pos =
        position_ -
        0.5 * b2Vec2(
                  Game::Instance().getWindow()->getWidth() / zoom_ - target_->getWidth(),
                  Game::Instance().getWindow()->getHeight() / zoom_ - target_->getHeight());

    if (pos.x < 0) {
        pos.x = 0;
    }

    if (pos.y < 0) {
        pos.y = 0;
    }

    return pos;
}

void Camera::update()
{
    Game& game = Game::Instance();
    position_ = target_->getPosition();

    float maxX = game.getLevel()->getMapWidth() -
                 (game.getWindow()->getWidth() / zoom_ + target_->getWidth()) * 0.5;
    float maxY = game.getLevel()->getMapHeight() -
                 (game.getWindow()->getHeight() / zoom_ + target_->getHeight()) * 0.5;

    if (position_.x > maxX) {
        position_.x = maxX;
    }

    if (position_.y > maxY) {
        position_.y = maxY;
    }


    if (position_.x < 0) {
        position_.x = 0;
    }

    if (position_.y < 0) {
        position_.y = 0;
    }
}

void Camera::setTarget(GameObject* const target)
{
    target_ = target;
}

void Camera::setPosition(const b2Vec2& position)
{
    position_ = position;
}

void Camera::setZoom(const float zoom)
{
    zoom_ = zoom;
}
