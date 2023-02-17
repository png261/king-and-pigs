#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "GameObject.hpp"
#include "SDL.hpp"
#include "PlatformerObject.hpp"

class Collision
{
public:
    static bool RectRect(SDL_Rect* A, SDL_Rect* B);
    static bool check(GameObject* A, GameObject* B);
    static bool checkAttack(PlatformerObject* A, PlatformerObject* B, int range);
};
#endif
