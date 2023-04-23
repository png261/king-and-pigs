#include "PhysicWorld.hpp"
#include "SDL.hpp"

namespace Utils {
SDL_Point b2Vec2ToSDLPoint(const b2Vec2& vec);
bool isProbable(int percent);
int meterToPixel(float meter);
float pixelToMeter(int pixel);
b2Vec2 meterToPixel(const b2Vec2& meter);
b2Vec2 pixelToMeter(const b2Vec2& pixel);
float radToDeg(float rad);
float degToRad(float deg);
} // namespace Utils
