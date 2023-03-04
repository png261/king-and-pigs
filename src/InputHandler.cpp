#include "InputHandler.hpp"

#include "Game.hpp"

InputHandler* InputHandler::Instance()
{
    static InputHandler* const s_pInstance = new InputHandler;
    return s_pInstance;
}

InputHandler::InputHandler()
    : m_keystates(nullptr)
    , m_pMousePosition(0, 0)
{}

void InputHandler::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: Game::Instance()->quit(); break;
        case SDL_KEYDOWN: onKeyDown(event); break;
        case SDL_KEYUP: onKeyUp(event); break;
        case SDL_MOUSEMOTION: onMouseMove(event); break;
        case SDL_MOUSEBUTTONDOWN: onMouseDown(event); break;
        case SDL_MOUSEBUTTONUP: onMouseUp(event); break;
        }
    }
}

void InputHandler::onMouseDown(SDL_Event const& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_LEFT: m_bMouseDown[MOUSE_LEFT] = true; break;
    case SDL_BUTTON_MIDDLE: m_bMouseDown[MOUSE_MIDDLE] = true; break;
    case SDL_BUTTON_RIGHT: m_bMouseDown[MOUSE_RIGHT] = true; break;
    }
}

void InputHandler::onMouseUp(SDL_Event const& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_LEFT: m_bMouseDown[MOUSE_LEFT] = false; break;
    case SDL_BUTTON_MIDDLE: m_bMouseDown[MOUSE_MIDDLE] = false; break;
    case SDL_BUTTON_RIGHT: m_bMouseDown[MOUSE_RIGHT] = false; break;
    }
}

void InputHandler::onKeyDown(SDL_Event const& event)
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp(SDL_Event const& event)
{
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event const& event)
{
    m_pMousePosition.x = event.motion.x;
    m_pMousePosition.y = event.motion.y;
}

bool InputHandler::isKeyDown(const KeyboardKey key) const
{
    return m_keystates != 0 && m_keystates[key] == 1;
}

void InputHandler::reset()
{
    m_keystates = nullptr;
    for (int i = 0; i < 3; i++) {
        m_bMouseDown[i] = false;
    }
}

b2Vec2 InputHandler::getMousePosition() const
{
    return m_pMousePosition;
}

bool InputHandler::isMouseDown(const MouseButton buttonID) const
{
    return m_bMouseDown[buttonID];
};
