#include "InputHandler.hpp"

#include "Game.hpp"
#include "InputDefinitions.hpp"

InputHandler* InputHandler::Instance()
{
    static InputHandler* const s_pInstance = new InputHandler;
    return s_pInstance;
}

InputHandler::InputHandler()
    : m_keyboard(nullptr)
    , m_mouse(0)
    , m_mousePosition(0, 0)
{
    int i;
    for (i = 0; i < KEYBOARD_SIZE; i++) {
        m_bKeyDown[i] = false;
        m_bKeyUp[i] = false;
    }

    for (i = 0; i < MOUSE_MAX; i++) {
        m_bMouseDown[i] = false;
        m_bMouseUp[i] = false;
    }
}

InputHandler::~InputHandler() {}

void InputHandler::update()
{
    int i;
    for (i = 0; i < KEYBOARD_SIZE; i++) {
        m_bKeyDown[i] = false;
        m_bKeyUp[i] = false;
    }

    for (i = 0; i < MOUSE_MAX; i++) {
        m_bMouseDown[i] = false;
        m_bMouseUp[i] = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Game::Instance()->quit();
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
    m_mouse = SDL_GetMouseState(nullptr, nullptr);

    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
        m_bMouseDown[MOUSE_LEFT] = true;
        break;
    case SDL_BUTTON_RIGHT:
        m_bMouseDown[MOUSE_RIGHT] = true;
        break;
    }
}

void InputHandler::onMouseUp(SDL_Event const& event)
{
    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
        m_bMouseUp[MOUSE_LEFT] = false;
        break;
    case SDL_BUTTON_RIGHT:
        m_bMouseUp[MOUSE_RIGHT] = false;
        break;
    }
}

void InputHandler::onKeyDown(SDL_Event const& event)
{
    m_keyboard = SDL_GetKeyboardState(0);

    int index = event.key.keysym.scancode;
    m_bKeyDown[index] = true;
}

void InputHandler::onKeyUp(SDL_Event const& event)
{
    m_keyboard = SDL_GetKeyboardState(0);

    int index = event.key.keysym.scancode;
    m_bKeyUp[index] = true;
}

void InputHandler::onMouseMove(SDL_Event const& event)
{
    m_mousePosition.x = event.motion.x;
    m_mousePosition.y = event.motion.y;
}

bool InputHandler::isKeyPressed(const KeyboardKey key) const
{
    return m_keyboard != 0 && m_keyboard[key] == 1;
}

bool InputHandler::isKeyDown(const KeyboardKey key) const
{
    return m_bKeyDown[key];
}

bool InputHandler::isKeyUp(const KeyboardKey key) const
{
    return m_bKeyUp[key];
}

void InputHandler::reset()
{
    m_keyboard = nullptr;
    int i;
    for (i = 0; i < KEYBOARD_SIZE; i++) {
        m_bKeyDown[i] = false;
        m_bKeyUp[i] = false;
    }

    m_mouse = 0;
    for (i = 0; i < MOUSE_MAX; i++) {
        m_bMouseDown[i] = false;
        m_bMouseUp[i] = false;
    }
}

b2Vec2 InputHandler::getMousePosition() const
{
    return m_mousePosition;
}

bool InputHandler::isMouseDown(const MouseButton button) const
{
    return m_bMouseDown[button];
};

bool InputHandler::isMouseUp(const MouseButton button) const
{
    return m_bMouseUp[button];
};

bool InputHandler::isMousePressed(const MouseButton button) const
{
    switch (button) {
    case MOUSE_LEFT:
        if (m_mouse & SDL_BUTTON(1)) return true;
        break;

    case MOUSE_RIGHT:
        if (m_mouse & SDL_BUTTON(3)) return true;
        break;

    default:
        break;
    }

    return false;
}

bool InputHandler::isMouseInside(Rectangle rectangle) const
{
    if ((m_mousePosition.x >= rectangle.x) && (m_mousePosition.x <= rectangle.x + rectangle.w) &&
        (m_mousePosition.y >= rectangle.y) && (m_mousePosition.y <= rectangle.y + rectangle.h))
        return true;

    return false;
}

void InputHandler::clean()
{
    this->reset();
}
