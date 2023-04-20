#include "Cursor.hpp"
#include "CONSTANT.hpp"
#include "InputHandler.hpp"
#include "SDL.hpp"
#include "TextureManager.hpp"

Cursor::Cursor()
    : size_(32)
    , is_hover_(false)
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
        TextureManager::Instance().draw("cursor_hover", position, size_, size_);
    } else {
        TextureManager::Instance().draw("cursor_normal", position, size_, size_);
    }
}

void Cursor::resetState()
{
    is_hover_ = false;
}

void Cursor::hover()
{
    is_hover_ = true;
}

bool Cursor::isHover() const
{
    return is_hover_;
}
