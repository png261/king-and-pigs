#include "Color.hpp"

Color::Color()
    : m_red(0)
    , m_green(0)
    , m_blue(0)
    , m_alpha(255)
{}

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    : m_red(r)
    , m_green(g)
    , m_blue(b)
    , m_alpha(a)
{}

Color::Color(Colors colorName)
{
    uint8_t r, g, b, a = 255;
    switch (colorName) {
    default:
    case WHITE:
        r = 255;
        g = 255;
        b = 255;
        break;
    case GRAY:
        r = 194;
        g = 214;
        b = 214;
        a = 100;
        break;
    case BLACK:
        r = 0;
        g = 0;
        b = 0;
        break;
    case RED:
        r = 255;
        g = 0;
        b = 0;
        break;
    case GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;
    case BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;
    case CYAN:
        r = 0;
        g = 255;
        b = 255;
        break;
    case YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;
    case MAGENTA:
        r = 255;
        g = 0;
        b = 255;
        break;
    }

    m_red = r;
    m_blue = b;
    m_green = g;
    m_alpha = a;
}

uint8_t Color::r() const
{
    return m_red;
}

uint8_t Color::g() const
{
    return m_green;
}

uint8_t Color::b() const
{
    return m_blue;
}

uint8_t Color::a() const
{
    return m_alpha;
}
