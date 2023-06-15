#include "Cursor.hpp"

#include "CONSTANT.hpp"
#include "InputManager.hpp"
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

void Cursor::draw() const
{
    TextureManager::Instance().draw(
        isHover() ? "cursor_hover" : "cursor_normal",
        InputManager::Instance().getMousePosition(),
        size_,
        size_);
}

void Cursor::reset()
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
