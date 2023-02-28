#include "InputHandler.hpp"

#include "Game.hpp"

InputHandler* InputHandler::Instance()
{
    static InputHandler* s_pInstance = new InputHandler;
    return s_pInstance;
}

InputHandler::InputHandler()
    : m_keystates(nullptr)
    , m_pMousePosition(new b2Vec2(0, 0))
{
    for (int i = 0; i < 3; i++) {
        m_bMouseButtonState.push_back(false);
    }
}

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: Game::Instance()->quit(); break;
        case SDL_KEYDOWN: onKeyDown(event); break;
        case SDL_KEYUP: onKeyUp(event); break;
        case SDL_MOUSEMOTION: onMouseMove(event); break;
        case SDL_MOUSEBUTTONDOWN: onMouseButtonDown(event); break;
        case SDL_MOUSEBUTTONUP: onMouseButtonUp(event); break;
        }
    }
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_LEFT: m_bMouseButtonState[MOUSE_LEFT] = true; break;
    case SDL_BUTTON_MIDDLE: m_bMouseButtonState[MOUSE_MIDDLE] = true; break;
    case SDL_BUTTON_RIGHT: m_bMouseButtonState[MOUSE_RIGHT] = true; break;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_LEFT: m_bMouseButtonState[MOUSE_LEFT] = false; break;
    case SDL_BUTTON_MIDDLE: m_bMouseButtonState[MOUSE_MIDDLE] = false; break;
    case SDL_BUTTON_RIGHT: m_bMouseButtonState[MOUSE_RIGHT] = false; break;
    }
}

void InputHandler::onKeyDown(SDL_Event& event)
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp(SDL_Event& event)
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_pMousePosition->x = event.motion.x;
    m_pMousePosition->y = event.motion.y;
}

bool InputHandler::isKeyDown(KeyboardKey key) const
{
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

void InputHandler::reset()
{
    m_keystates = nullptr;
    for (int i = 0; i < 3; i++) {
        m_bMouseButtonState[i] = false;
    }
}

b2Vec2* InputHandler::getMousePosition() const
{
    return m_pMousePosition;
}

bool InputHandler::isMouseButtonDown(MouseButton buttonID) const
{
    return m_bMouseButtonState[buttonID];
};
