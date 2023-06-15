#include "Camera.hpp"

#include "Game.hpp"
#include "Utils.hpp"

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

float Camera::getX() const
{
    return getPosition().x;
}

float Camera::getY() const
{
    return getPosition().y;
}

void Camera::update()
{
    const Game& game = Game::Instance();
    position_ = target_->getPosition();

    const float maxX = game.getLevel()->getMapWidth() -
                       (game.getWindow()->getWidth() / zoom_ + target_->getWidth()) * 0.5;
    const float maxY = game.getLevel()->getMapHeight() -
                       (game.getWindow()->getHeight() / zoom_ + target_->getHeight()) * 0.5;

    Utils::limitInRange<float>(position_.x, 0, maxX);
    Utils::limitInRange<float>(position_.y, 0, maxY);
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
