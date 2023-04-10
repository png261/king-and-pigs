#pragma once

#include <stdint.h> // uint8_t
#include <string>

class Color final
{
public:
    enum Colors { WHITE, BLACK, RED, GREEN, BLUE, CYAN, YELLOW, MAGENTA };
    Color();
    Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
    Color(Colors colorName);
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
