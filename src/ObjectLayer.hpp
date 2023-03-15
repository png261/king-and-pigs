#pragma once

#include <vector>
#include "Layer.hpp"

class GameObject;

class ObjectLayer final : public Layer
{
public:
    virtual ~ObjectLayer();

    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects();

private:
    std::vector<GameObject*> m_gameObjects;
};
