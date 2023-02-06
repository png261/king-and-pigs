#include "CollisionManager.h"
#include "Collision.h"
#include <iostream>

void CollisionManager::checkPlayerEnemyCollision(Player *pPlayer,
                                                 Enemy *pEnemy) {
    SDL_Rect *pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();

    SDL_Rect *pRect2 = new SDL_Rect();
    pRect2->x = pEnemy->getPosition().getX();
    pRect2->y = pEnemy->getPosition().getY();
    pRect2->w = pEnemy->getWidth();
    pRect2->h = pEnemy->getHeight();

    if (RectRect(pRect1, pRect2)) {
        std::cout << "col" << std::endl;
        pPlayer->collision();
    }
}
