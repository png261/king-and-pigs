#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Enemy.h"
#include "GameObject.h"
#include "Player.h"
#include <vector>

class CollisionManager {
  public:
    void checkPlayerEnemyCollision(Player *pPlayer, Enemy *enemy);
};

#endif
