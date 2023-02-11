#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include "GameObject.h"

const static int s_buffer = 4;

static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
    int aHBuf = A->h / s_buffer;
    int aWBuf = A->w / s_buffer;

    int bHBuf = B->h / s_buffer;
    int bWBuf = B->w / s_buffer;

    // if the bottom of A is less than the top of B - no collision
    if ((A->y + A->h) - aHBuf <= B->y + bHBuf) {
        return false;
    }

    // if the top of A is more than the bottom of B = no collision
    if (A->y + aHBuf >= (B->y + B->h) - bHBuf) {
        return false;
    }

    // if the right of A is less than the left of B - no collision
    if ((A->x + A->w) - aWBuf <= B->x + bWBuf) {
        return false;
    }

    // if the left of A is more than the right of B - no collision
    if (A->x + aWBuf >= (B->x + B->w) - bWBuf) {
        return false;
    }

    // otherwise there has been a collision
    return true;
}

static bool checkCollision(GameObject* A, GameObject* B)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = A->getPosition().getX();
    pRect1->y = A->getPosition().getY();
    pRect1->w = A->getWidth();
    pRect1->h = A->getHeight();

    SDL_Rect* pRect2 = new SDL_Rect();
    pRect2->x = B->getPosition().getX();
    pRect2->y = B->getPosition().getY();
    pRect2->w = B->getWidth();
    pRect2->h = B->getHeight();

    return RectRect(pRect1, pRect2);
}

#endif
