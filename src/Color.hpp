#pragma once

#include <stdint.h>

#include <string>

enum class ColorName { WHITE, GRAY, BLACK, RED, GREEN, BLUE, CYAN, YELLOW, MAGENTA };

class Color final
{
public:
    Color();
    Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
    Color(const ColorName color);
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
