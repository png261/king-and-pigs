#pragma once

#include <stdint.h> // uint8_t
#include <string>

class Color final
{
public:
    enum Colors { WHITE, GRAY, BLACK, RED, GREEN, BLUE, CYAN, YELLOW, MAGENTA };
    Color();
    Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
    Color(Colors color);
    uint8_t r() const;
    uint8_t g() const;
    uint8_t b() const;
    uint8_t a() const;

private:
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
    uint8_t alpha_;
};
