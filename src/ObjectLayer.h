#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include "CollisionManager.h"
#include "Layer.h"
#include <iostream>
#include <vector>

class GameObject;

class ObjectLayer : public Layer {
  public:
    virtual ~ObjectLayer();

    virtual void update(Level *pLevel);
    virtual void render();

    std::vector<GameObject *> *getGameObjects() { return &m_gameObjects; }

  private:
    CollisionManager m_collisionManager;
    std::vector<GameObject *> m_gameObjects;
};

#endif
