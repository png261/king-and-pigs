#include "LoaderParams.hpp"

LoaderParams::LoaderParams(
    const int x,
    const int y,
    const int width,
    const int height,
    const int textureWidth,
    const int textureHeight,
    const int textureX,
    const int textureY)
    : m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
    , m_textureWidth(textureWidth)
    , m_textureHeight(textureHeight)
    , m_textureX(textureX)
    , m_textureY(textureY)
{}

int LoaderParams::x() const
{
    return m_x;
}

int LoaderParams::y() const
{
    return m_y;
}

int LoaderParams::width() const
{
    return m_width;
}

int LoaderParams::height() const
{
    return m_height;
}

int LoaderParams::textureWidth() const
{
    return m_textureWidth;
}

int LoaderParams::textureHeight() const
{
    return m_textureHeight;
}

int LoaderParams::textureX() const
{
    return m_textureX;
}

int LoaderParams::textureY() const
{
    return m_textureY;
}
