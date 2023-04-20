#include "Button.hpp"

#include "CONSTANT.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "SoundManager.hpp"

Button::Button(std::string text, int x, int y, int width, int height)
    : UiObject()
    , is_disabled_(false)
    , text_(text)
    , rectangle_(x, y, width, height)
    , callback_(nullptr)
{
    SoundManager::Instance().loadSFX(SOUND_DIRECTORY + "Button/clicked.mp3", "button clicked");
}

void Button::draw()
{
    if (isDisabled()) {
        Game::Instance().getWindow()->drawBox(rectangle_, Color::GRAY);
    } else {
        Game::Instance().getWindow()->drawBox(rectangle_);
    }

    Game::Instance().getWindow()->print(
        text_,
        40,
        rectangle_.x + rectangle_.w * 0.5f,
        rectangle_.y + rectangle_.h * 0.5f);
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

void Button::onClick(std::function<void()> callback)
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
