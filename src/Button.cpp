#include "Button.hpp"
#include <iterator>

#include "CONSTANT.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

Button::Button()
    : UiObject()
    , callback_(nullptr)
    , is_disabled_(false)
    , border_radius_(15)
    , font_color_(Color::BLACK)
    , normal_color_(Color::WHITE)
    , hovered_color_(Color::GRAY)
    , disabled_color_(Color::GRAY)
{}

void Button::load(std::unique_ptr<LoaderParams> const& params)
{
    rectangle_ = Rectangle(params->x(), params->y(), params->width(), params->height());
    SoundManager::Instance().loadSFX(SOUND_DIRECTORY + "button/clicked.mp3", "button clicked");
}

void Button::draw() const
{
    Color color_hovered{183, 183, 183};

    if (isDisabled()) {
        Game::Instance().getWindow()->drawBox(rectangle_, border_radius_, disabled_color_);
    } else if (isHovered()) {
        Game::Instance().getWindow()->drawBox(rectangle_, border_radius_, hovered_color_);
    } else {
        Game::Instance().getWindow()->drawBox(rectangle_, border_radius_, normal_color_);
    }

    if (!title_.empty()) {
        Game::Instance().getWindow()->print(
            title_,
            rectangle_.x() + rectangle_.w() * 0.5f,
            rectangle_.y() + rectangle_.h() * 0.5f,
            40,
            font_color_);
    }

    if (!texture_id_.empty()) {
        TextureManager::Instance()
            .draw(texture_id_, {rectangle_.x(), rectangle_.y()}, rectangle_.w(), rectangle_.h());
    }
};

void Button::setTitle(const std::string& title)
{
    title_ = title;
}

void Button::update()
{
    if (isDisabled()) {
        return;
    }

    is_hovered_ = InputHandler::Instance().isMouseInside(rectangle_);

    if (callback_ != nullptr && isHovered()) {
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

void Button::setTexture(const std::string& texture_id)
{
    texture_id_ = texture_id;
}

void Button::setBorderRadius(const int border_radius)
{
    border_radius_ = border_radius;
}

bool Button::isHovered() const
{
    return is_hovered_;
}

void Button::setBackgroundColor(
    const Color& normal_color,
    const Color& hovered_color,
    const Color& disabled_color)
{
    normal_color_ = normal_color;
    hovered_color_ = hovered_color;
    disabled_color_ = disabled_color;
};
