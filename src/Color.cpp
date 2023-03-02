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
