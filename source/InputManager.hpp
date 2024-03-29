#pragma once

#include <memory>
#include <vector>

#include "InputDefinitions.hpp"
#include "PhysicManager.hpp"
#include "SDL.hpp"
#include "Shapes.hpp"

class InputManager final
{
public:
    static InputManager& Instance();
    InputManager(InputManager const&) = delete;
    InputManager& operator=(InputManager const&) = delete;

    void update(SDL_Event& event);
    void refresh();
    void reset();
    void clean();

    b2Vec2 getMousePosition() const;

    bool isKeyDown(const KeyboardKey key) const;
    bool isKeyUp(const KeyboardKey key) const;
    bool isKeyPressed(const KeyboardKey key) const;

    bool isMouseDown(const MouseButton button) const;
    bool isMouseUp(const MouseButton button) const;
    bool isMousePressed(const MouseButton button) const;
    bool isMouseInside(const Rectangle& rectangle) const;

private:
    InputManager();

    void onKeyDown(SDL_Event const& event);
    void onKeyUp(SDL_Event const& event);

    void onMouseMove(SDL_Event const& event);
    void onMouseDown(SDL_Event const& event);
    void onMouseUp(SDL_Event const& event);

    const Uint8* keyboard_;
    bool is_key_down_[KEYBOARD_SIZE];
    bool is_key_up_[KEYBOARD_SIZE];

    uint32_t mouse_;
    b2Vec2 mouse_position_;
    bool is_mouse_down_[MOUSE_MAX];
    bool is_mouse_up_[MOUSE_MAX];
};
