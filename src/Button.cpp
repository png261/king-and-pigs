#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "SoundManager.hpp"

Button::Button(std::string text, int x, int y, int width, int height)
    : UiObject()
    , m_text(text)
    , m_rectangle(x, y, width, height)
    , m_callback(nullptr)
{
    SoundManager::Instance().loadSFX(SOUND_DIRECTORY + "Button/clicked.mp3", "button clicked");
}

void Button::draw()
{
    Game::Instance().getWindow()->drawBox(m_rectangle);
    Game::Instance().getWindow()->print(
        m_text,
        40,
        m_rectangle.x + m_rectangle.w * 0.5f,
        m_rectangle.y + m_rectangle.h * 0.5f);
};

void Button::update()
{
    if (InputHandler::Instance().isMouseInside(m_rectangle)) {
        if (InputHandler::Instance().isMouseDown(MOUSE_LEFT)) {
            SoundManager::Instance().playSFX("button clicked");
            m_callback();
        }
    }
};

void Button::onClick(std::function<void()> callback)
{
    m_callback = callback;
}
