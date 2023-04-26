#include "InputHandler.hpp"

#include "Game.hpp"
#include "InputDefinitions.hpp"

InputHandler& InputHandler::Instance()
{
    static InputHandler instance{};
    return instance;
}

InputHandler::InputHandler()
    : keyboard_(nullptr)
    , mouse_(0)
    , mouse_position_(0, 0)
{
    int i;
    for (i = 0; i < KEYBOARD_SIZE; ++i) {
        is_key_down_[i] = false;
        is_key_up_[i] = false;
    }

    for (i = 0; i < MOUSE_MAX; ++i) {
        is_mouse_down_[i] = false;
        is_mouse_up_[i] = false;
    }
}

void InputHandler::update()
{
    int i;
    for (i = 0; i < KEYBOARD_SIZE; ++i) {
        is_key_down_[i] = false;
        is_key_up_[i] = false;
    }

    for (i = 0; i < MOUSE_MAX; ++i) {
        is_mouse_down_[i] = false;
        is_mouse_up_[i] = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Game::Instance().quit();
            break;
        case SDL_KEYDOWN:
            onKeyDown(event);
            break;
        case SDL_KEYUP:
            onKeyUp(event);
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseUp(event);
            break;
        }
    }
}

void InputHandler::onMouseDown(SDL_Event const& event)
{
    mouse_ = SDL_GetMouseState(nullptr, nullptr);

    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
        is_mouse_down_[MOUSE_LEFT] = true;
        break;
    case SDL_BUTTON_RIGHT:
        is_mouse_down_[MOUSE_RIGHT] = true;
        break;
    }
}

void InputHandler::onMouseUp(SDL_Event const& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
        is_mouse_up_[MOUSE_LEFT] = false;
        break;
    case SDL_BUTTON_RIGHT:
        is_mouse_up_[MOUSE_RIGHT] = false;
        break;
    }
}

void InputHandler::onKeyDown(SDL_Event const& event)
{
    keyboard_ = SDL_GetKeyboardState(0);

    int index = event.key.keysym.scancode;
    is_key_down_[index] = true;
}

void InputHandler::onKeyUp(SDL_Event const& event)
{
    keyboard_ = SDL_GetKeyboardState(0);

    int index = event.key.keysym.scancode;
    is_key_up_[index] = true;
}

void InputHandler::onMouseMove(SDL_Event const& event)
{
    mouse_position_.x = event.motion.x;
    mouse_position_.y = event.motion.y;
}

bool InputHandler::isKeyPressed(const KeyboardKey key) const
{
    return keyboard_ != 0 && keyboard_[key] == 1;
}

bool InputHandler::isKeyDown(const KeyboardKey key) const
{
    return is_key_down_[key];
}

bool InputHandler::isKeyUp(const KeyboardKey key) const
{
    return is_key_up_[key];
}

void InputHandler::reset()
{
    keyboard_ = nullptr;
    int i;
    for (i = 0; i < KEYBOARD_SIZE; ++i) {
        is_key_down_[i] = false;
        is_key_up_[i] = false;
    }

    mouse_ = 0;
    for (i = 0; i < MOUSE_MAX; ++i) {
        is_mouse_down_[i] = false;
        is_mouse_up_[i] = false;
    }
}

b2Vec2 InputHandler::getMousePosition() const
{
    return mouse_position_;
}

bool InputHandler::isMouseDown(const MouseButton button) const
{
    return is_mouse_down_[button];
};

bool InputHandler::isMouseUp(const MouseButton button) const
{
    return is_mouse_up_[button];
};

bool InputHandler::isMousePressed(const MouseButton button) const
{
    switch (button) {
    case MOUSE_LEFT:
        if (mouse_ & SDL_BUTTON(1)) return true;
        break;

    case MOUSE_RIGHT:
        if (mouse_ & SDL_BUTTON(3)) return true;
        break;

    default:
        break;
    }

    return false;
}

bool InputHandler::isMouseInside(const Rectangle& rectangle) const
{
    if ((mouse_position_.x >= rectangle.x()) &&
        (mouse_position_.x <= rectangle.x() + rectangle.w()) &&
        (mouse_position_.y >= rectangle.y()) &&
        (mouse_position_.y <= rectangle.y() + rectangle.h()))
        return true;

    return false;
}

void InputHandler::clean()
{
    reset();
}
