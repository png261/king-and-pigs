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
    , m_bHovered(false)
{
    m_animations[NORMAL] = std::make_unique<Animation>("button normal", 250, 70);
    m_animations[HOVERED] = std::make_unique<Animation>("button hovered", 250, 70);
    m_animations[PRESSED] = std::make_unique<Animation>("button pressed", 250, 70);

    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
    SoundManager::Instance()->loadSFX(SOUND_DIR + "Button/clicked.mp3", "button clicked");
}

Button::~Button() {}

void Button::draw()
{
    /* m_animations[m_curAnimation]->draw(b2Vec2(m_rectangle.x, m_rectangle.y)); */
    Game::Instance()->getWindow()->drawBox(m_rectangle);
    Game::Instance()->getWindow()->print(
        m_text,
        40,
        m_rectangle.x + m_rectangle.w / 2,
        m_rectangle.y + m_rectangle.h / 2);
};

void Button::update()
{
    int newAnimation = m_curAnimation;

    if (InputHandler::Instance()->isMouseInside(m_rectangle)) {
        m_bHovered = true;
        newAnimation = HOVERED;
    } else {
        m_bHovered = false;
        newAnimation = NORMAL;
    }

    if (m_bHovered) {
        if (InputHandler::Instance()->isMouseDown(MOUSE_LEFT)) {
            SoundManager::Instance()->playSFX("button clicked");
            m_callback();
        }
    }

    /*     if (newAnimation != m_curAnimation) { */
    /*         m_animations[m_curAnimation]->stop(); */
    /*         m_curAnimation = newAnimation; */
    /*         m_animations[m_curAnimation]->start(); */
    /*     } */
};

void Button::onClick(std::function<void()> callback)
{
    m_callback = callback;
}
