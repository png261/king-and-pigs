#include "Utils.hpp"

SDL_Point Utils::b2Vec2ToSDLPoint(const b2Vec2& vec)
{
    return {static_cast<int>(vec.x), static_cast<int>(vec.y)};
};
