#include "Cursor.hpp"
#include "CONSTANT.hpp"
#include "InputHandler.hpp"
#include "SDL.hpp"
#include "TextureManager.hpp"

Cursor::Cursor()
    : m_size(32)
    , m_bHover(false)
{}

void Cursor::init()
{
    SDL::hideCursor();
    TextureManager::Instance().load(IMAGE_DIRECTORY + "ui/cursor/normal.png", "cursor_normal");
    TextureManager::Instance().load(IMAGE_DIRECTORY + "ui/cursor/hover.png", "cursor_hover");
}

void Cursor::draw()
{
    b2Vec2 position = InputHandler::Instance().getMousePosition();
    if (isHover()) {
        TextureManager::Instance().draw("cursor_hover", position, m_size, m_size);
    } else {
        TextureManager::Instance().draw("cursor_normal", position, m_size, m_size);
    }
}

void Cursor::resetState()
{
    m_bHover = false;
}

void Cursor::hover()
{
    m_bHover = true;
}

bool Cursor::isHover() const
{
    return m_bHover;
}
