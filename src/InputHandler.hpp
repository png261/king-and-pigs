#pragma once

#include <vector>
#include "InputDefinitions.hpp"
#include "PhysicWorld.hpp"
#include "SDL.hpp"
#include "Shapes.hpp"

class InputHandler final
{
public:
    static InputHandler* Instance();

    void update();

    b2Vec2 getMousePosition() const;

    bool isKeyDown(const KeyboardKey key) const;
    bool isKeyUp(const KeyboardKey key) const;
    bool isKeyPressed(const KeyboardKey key) const;

    bool isMouseDown(const MouseButton button) const;
    bool isMouseUp(const MouseButton button) const;
    bool isMousePressed(const MouseButton button) const;
    bool isMouseInside(const Rectangle rectangle) const;

    void reset();
    void clean();

private:
    InputHandler();
    ~InputHandler();

    void onKeyDown(SDL_Event const& event);
    void onKeyUp(SDL_Event const& event);

    void onMouseMove(SDL_Event const& event);
    void onMouseDown(SDL_Event const& event);
    void onMouseUp(SDL_Event const& event);

    const Uint8* m_keyboard;
    bool m_bKeyDown[KEYBOARD_SIZE];
    bool m_bKeyUp[KEYBOARD_SIZE];

    uint32_t m_mouse;
    b2Vec2 m_mousePosition;
    bool m_bMouseDown[MOUSE_MAX];
    bool m_bMouseUp[MOUSE_MAX];
};
