#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h> // uint8_t

class Color
{
public:
    Color();
    Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
    uint8_t r() const;
    uint8_t g() const;
    uint8_t b() const;
    uint8_t a() const;

private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
};

#endif
