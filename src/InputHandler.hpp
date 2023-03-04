#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <vector>
#include "Box2D.hpp"
#include "InputDefinitions.hpp"
#include "SDL.hpp"

class InputHandler
{
public:
    static InputHandler* Instance();

    void handleEvents();

    b2Vec2 getMousePosition() const;

    bool isKeyDown(const KeyboardKey key) const;

    bool isMouseDown(const MouseButton buttonID) const;

    void reset();

private:
    InputHandler();

    void onKeyDown(SDL_Event const& event);
    void onKeyUp(SDL_Event const& event);

    void onMouseMove(SDL_Event const& event);
    void onMouseDown(SDL_Event const& event);
    void onMouseUp(SDL_Event const& event);

    b2Vec2 m_pMousePosition;
    bool m_bMouseDown[MOUSE_MAX];

    const Uint8* m_keystates;
};

#endif
