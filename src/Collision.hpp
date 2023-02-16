#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "GameObject.hpp"
#include "PlatformerObject.hpp"

class Collision
{
public:
    static bool RectRect(SDL_Rect* A, SDL_Rect* B);
    static bool check(GameObject* A, GameObject* B);
    static bool checkAttack(PlatformerObject* A, PlatformerObject* B, int range);
};
#endif
