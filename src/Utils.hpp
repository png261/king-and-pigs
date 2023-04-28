#include <json/json.h>
#include "PhysicWorld.hpp"
#include "SDL.hpp"

namespace Utils {
SDL_Point b2Vec2ToSDLPoint(const b2Vec2& vec);
bool isProbable(const int percent);
int meterToPixel(const float meter);
float pixelToMeter(const int pixel);
b2Vec2 meterToPixel(const b2Vec2& meter);
b2Vec2 pixelToMeter(const b2Vec2& pixel);
float radToDeg(const float rad);
float degToRad(const float deg);
Color hexToRgba(const std::string& hex);
void openLink(const std::string& link);
Json::Value read_json_file(const std::string& path);
} // namespace Utils
