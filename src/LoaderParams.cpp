#include "LoaderParams.hpp"

LoaderParams::LoaderParams(const int x, const int y, const int width, const int height)
    : x_(x)
    , y_(y)
    , width_(width)
    , height_(height)
{}

int LoaderParams::x() const
{
    return x_;
}

int LoaderParams::y() const
{
    return y_;
}

int LoaderParams::width() const
{
    return width_;
}

int LoaderParams::height() const
{
    return height_;
}
