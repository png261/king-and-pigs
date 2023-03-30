#include "Button.hpp"
#include "InputHandler.hpp"

Button::Button(int x, int y, int width, int height)
    : UiObject()
    , m_rectangle(x, y, width, height)
    , m_callback(nullptr)
    , m_bHovered(false)
{
    m_animations[NORMAL] = new Animation("button normal", 178, 64);
    m_animations[HOVERED] = new Animation("button hovered", 178, 64);
    m_animations[PRESSED] = new Animation("button pressed", 178, 64);

    m_curAnimation = NORMAL;
    m_animations[m_curAnimation]->start();
}

Button::~Button() {}

void Button::load(){};

void Button::draw()
{
    m_animations[m_curAnimation]->draw(b2Vec2(m_rectangle.x, m_rectangle.y));
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
            m_callback();
        }
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
};

void Button::setCallback(void (*callback)())
{
    m_callback = callback;
}