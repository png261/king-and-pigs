#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Enemy.h"
#include "GameObject.h"
#include "Player.h"
#include <vector>

class CollisionManager {
  public:
    static void
    checkPlayerEnemyCollision(Player *pPlayer,
                              const std::vector<GameObject *> &objects);
};

#endif
