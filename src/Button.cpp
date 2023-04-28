#include "Button.hpp"

#include "CONSTANT.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "SoundManager.hpp"

Button::Button(const std::string& text, const float border_radius)
    : UiObject()
    , is_disabled_(false)
    , text_(text)
    , border_radius_(border_radius)
    , callback_(nullptr)
{
    SoundManager::Instance().loadSFX(SOUND_DIRECTORY + "button/clicked.mp3", "button clicked");
}

void Button::load(std::unique_ptr<LoaderParams> const& params)
{
    rectangle_ = Rectangle(params->x(), params->y(), params->width(), params->height());
}

void Button::draw() const
{
    if (isDisabled()) {
        Game::Instance().getWindow()->drawBox(rectangle_, border_radius_, Color::GRAY);
    } else {
        Game::Instance().getWindow()->drawBox(rectangle_, border_radius_);
    }

    Game::Instance().getWindow()->print(
        text_,
        rectangle_.x() + rectangle_.w() * 0.5f,
        rectangle_.y() + rectangle_.h() * 0.5f,
        40);
};

void Button::update()
{
    if (isDisabled()) {
        return;
    }

    if (InputHandler::Instance().isMouseInside(rectangle_)) {
        Game::Instance().getCursor()->hover();
        if (InputHandler::Instance().isMouseDown(MOUSE_LEFT)) {
            SoundManager::Instance().playSFX("button clicked");
            callback_();
        }
    }
};

void Button::onClick(const std::function<void()>& callback)
{
    callback_ = callback;
}

void Button::disable()
{
    is_disabled_ = true;
}

void Button::enable()
{
    is_disabled_ = false;
}

bool Button::isDisabled() const
{
    return is_disabled_;
}
