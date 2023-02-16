#ifndef OBJECT_LAYER_HPP
#define OBJECT_LAYER_HPP

#include <iostream>
#include <vector>
#include "Layer.hpp"

class GameObject;

class ObjectLayer : public Layer
{
public:
    virtual ~ObjectLayer();

    virtual void update(Level* pLevel);
    virtual void render();

    std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
    std::vector<GameObject*> m_gameObjects;
};

#endif
