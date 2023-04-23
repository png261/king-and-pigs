#include "Utils.hpp"
#include "CONSTANT.hpp"

SDL_Point Utils::b2Vec2ToSDLPoint(const b2Vec2& vec)
{
    return {static_cast<int>(vec.x), static_cast<int>(vec.y)};
};

bool Utils::isProbable(int percent)
{
    srand(time(0));
    return (rand() % 100) < percent;
}

int Utils::meterToPixel(const float meter)
{
    return static_cast<int>(floor(meter * PIXEL_PER_METER));
}

float Utils::pixelToMeter(const int pixel)
{
    return static_cast<float>(pixel * METER_PER_PIXEL);
}

b2Vec2 Utils::meterToPixel(const b2Vec2& meter)
{
    return PIXEL_PER_METER * meter;
};

b2Vec2 Utils::pixelToMeter(const b2Vec2& pixel)
{
    return METER_PER_PIXEL * pixel;
};

float Utils::radToDeg(const float rad)
{
    return rad * DEG_PER_RAD;
};

float Utils::degToRad(const float deg)
{
    return deg * RAD_PER_DEG;
};
