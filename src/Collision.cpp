#include "Collision.hpp"

bool Collision::RectRect(SDL_Rect* A, SDL_Rect* B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A->x;
    rightA = A->x + A->w;
    topA = A->y;
    bottomA = A->y + A->h;

    leftB = B->x;
    rightB = B->x + B->w;
    topB = B->y;
    bottomB = B->y + B->h;

    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    return true;
};

bool Collision::check(GameObject* A, GameObject* B)
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
};

bool Collision::checkAttack(PlatformerObject* A, PlatformerObject* B, int range)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = A->getPosition().getX();
    if (A->isFlipped()) {
        pRect1->x -= 2 * range;
    }
    pRect1->y = A->getPosition().getY();
    pRect1->w = A->getWidth() + range;
    pRect1->h = A->getHeight();

    SDL_Rect* pRect2 = new SDL_Rect();
    pRect2->x = B->getPosition().getX();
    pRect2->y = B->getPosition().getY();
    pRect2->w = B->getWidth();
    pRect2->h = B->getHeight();

    return RectRect(pRect1, pRect2);
};
