#include "MenuButton.hpp"
#include "InputHandler.hpp"

MenuButton::MenuButton()
    : PlatformerObject()
    , m_callback(0)
    , m_bReleased(true)
{}

void MenuButton::load(const LoaderParams* const pParams)
{
    PlatformerObject::load(pParams);
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    PlatformerObject::draw();
}

void MenuButton::update()
{
    b2Vec2* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if (pMousePos->x < (m_position.x + m_width) && pMousePos->x > m_position.x &&
        pMousePos->y < (m_position.y + m_height) && pMousePos->y > m_position.y) {
        if (TheInputHandler::Instance()->isMouseButtonDown(MOUSE_LEFT) && m_bReleased) {
            m_currentFrame = CLICKED;

            if (m_callback != 0) {
                m_callback();
            }

            m_bReleased = false;
        } else if (!TheInputHandler::Instance()->isMouseButtonDown(MOUSE_LEFT)) {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    } else {
        m_currentFrame = MOUSE_OUT;
    }
}

std::string MenuButton::type() const
{
    return "MenuButton";
}
