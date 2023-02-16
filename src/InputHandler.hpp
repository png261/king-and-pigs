#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SDL2/SDL.h>

#include <vector>

#include "Vector2D.hpp"

enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2,
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        static InputHandler* s_pInstance = new InputHandler;
        return s_pInstance;
    }
    void update();
    Vector2D* getMousePosition() const { return m_pMousePosition; }

    bool isKeyDown(SDL_Scancode key) const;
    bool getMouseButtonState(mouse_buttons buttonID) { return m_bMouseButtonState[buttonID]; };

    void reset();

private:
    InputHandler();

    void onKeyDown(SDL_Event& event);
    void onKeyUp(SDL_Event& event);

    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    Vector2D* m_pMousePosition;
    std::vector<bool> m_bMouseButtonState;

    const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;

#endif
