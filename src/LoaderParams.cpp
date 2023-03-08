#include "LoaderParams.hpp"

LoaderParams::LoaderParams(const int x, const int y, const int width, const int height)
    : m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
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
