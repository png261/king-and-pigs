#pragma once

#include <vector>
#include "Layer.hpp"

class GameObject;

class ObjectLayer final : public Layer
{
public:
    ~ObjectLayer();

    void update();
    void render();

    std::vector<GameObject*>* getGameObjects();
    void addGameObject(GameObject*);

private:
    std::vector<GameObject*> m_gameObjects;
    std::vector<GameObject*> m_willDelete;
};
