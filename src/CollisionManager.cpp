#include "CollisionManager.h"
#include <iostream>
#include "Collision.h"

void CollisionManager::checkPlayerEnemyCollision(
    Player* pPlayer,
    const std::vector<GameObject*>& objects)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();

    for (auto& obj : objects) {
        if (obj->type() != std::string("Enemy") || !obj->updating()) {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = obj->getPosition().getX();
        pRect2->y = obj->getPosition().getY();
        pRect2->w = obj->getWidth();
        pRect2->h = obj->getHeight();

        if (RectRect(pRect1, pRect2)) {
            if (!obj->dead() && !obj->dying()) {
                pPlayer->collision();
                obj->collision();
            }
        }

        delete pRect2;
    }

    delete pRect1;
}
