#include "InputManager.hpp"

#include "Game.hpp"
#include "InputDefinitions.hpp"

InputManager& InputManager::Instance()
{
    static InputManager instance{};
    return instance;
}

InputManager::InputManager()
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

void InputManager::update()
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

void InputManager::onMouseDown(SDL_Event const& event)
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

void InputManager::onMouseUp(SDL_Event const& event)
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

void InputManager::onKeyDown(SDL_Event const& event)
{
    keyboard_ = SDL_GetKeyboardState(0);

    int index = event.key.keysym.scancode;
    is_key_down_[index] = true;
}

void InputManager::onKeyUp(SDL_Event const& event)
{
    keyboard_ = SDL_GetKeyboardState(0);

    int index = event.key.keysym.scancode;
    is_key_up_[index] = true;
}

void InputManager::onMouseMove(SDL_Event const& event)
{
    mouse_position_.x = event.motion.x;
    mouse_position_.y = event.motion.y;
}

bool InputManager::isKeyPressed(const KeyboardKey key) const
{
    return keyboard_ != 0 && keyboard_[key] == 1;
}

bool InputManager::isKeyDown(const KeyboardKey key) const
{
    return is_key_down_[key];
}

bool InputManager::isKeyUp(const KeyboardKey key) const
{
    return is_key_up_[key];
}

void InputManager::reset()
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

b2Vec2 InputManager::getMousePosition() const
{
    return mouse_position_;
}

bool InputManager::isMouseDown(const MouseButton button) const
{
    return is_mouse_down_[button];
};

bool InputManager::isMouseUp(const MouseButton button) const
{
    return is_mouse_up_[button];
};

bool InputManager::isMousePressed(const MouseButton button) const
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

bool InputManager::isMouseInside(const Rectangle& rectangle) const
{
    if ((mouse_position_.x >= rectangle.x()) &&
        (mouse_position_.x <= rectangle.x() + rectangle.w()) &&
        (mouse_position_.y >= rectangle.y()) &&
        (mouse_position_.y <= rectangle.y() + rectangle.h()))
        return true;

    return false;
}

void InputManager::clean()
{
    reset();
}
