#include "Color.hpp"

Color::Color()
    : red_(0)
    , green_(0)
    , blue_(0)
    , alpha_(255)
{}

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    : red_(r)
    , green_(g)
    , blue_(b)
    , alpha_(a)
{}

Color::Color(const ColorName color)
{
    uint8_t r, g, b, a = 255;
    switch (color) {
    default:
    case ColorName::WHITE:
        r = 255;
        g = 255;
        b = 255;
        break;
    case ColorName::GRAY:
        r = 194;
        g = 214;
        b = 214;
        break;
    case ColorName::BLACK:
        r = 0;
        g = 0;
        b = 0;
        break;
    case ColorName::RED:
        r = 255;
        g = 0;
        b = 0;
        break;
    case ColorName::GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;
    case ColorName::BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;
    case ColorName::CYAN:
        r = 0;
        g = 255;
        b = 255;
        break;
    case ColorName::YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;
    case ColorName::MAGENTA:
        r = 255;
        g = 0;
        b = 255;
        break;
    }

    red_ = r;
    blue_ = b;
    green_ = g;
    alpha_ = a;
}

uint8_t Color::r() const
{
    return red_;
}

uint8_t Color::g() const
{
    return green_;
}

uint8_t Color::b() const
{
    return blue_;
}

uint8_t Color::a() const
{
    return alpha_;
}
