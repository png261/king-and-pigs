#include "Utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "CONSTANT.hpp"


SDL_Point Utils::b2Vec2ToSDLPoint(const b2Vec2& vec)
{
    return {static_cast<int>(vec.x), static_cast<int>(vec.y)};
};

bool Utils::isProbable(const int percent)
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

Color Utils::hexToRgba(const std::string& hex)
{
    uint8_t r = std::stoi(hex.substr(1, 2), 0, 16);
    uint8_t g = std::stoi(hex.substr(3, 2), 0, 16);
    uint8_t b = std::stoi(hex.substr(5, 2), 0, 16);
    uint8_t a = 1.0f;
    return {r, g, b, a};
}

void Utils::openLink(const std::string& link)
{
#ifdef _WIN32
    // Windows command to open link
    system(("start " + link).c_str());
#elif __linux__
    // Linux command to open link
    system(("xdg-open " + link).c_str());
#endif
}

nlohmann::json Utils::read_json_file(const std::string& path)
{
    std::ifstream json_file(path);
    if (!json_file.is_open()) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load: ") + path);
    }
    return nlohmann::json::parse(json_file);
}
