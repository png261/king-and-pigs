#pragma once

#include <memory>
#include <vector>
#include "Layer.hpp"

class GameObject;

class ObjectLayer final : public Layer
{
public:
    ~ObjectLayer();

    void update();
    void render() const;

    std::vector<std::unique_ptr<GameObject>>* getGameObjects();
    void addGameObject(GameObject*);

private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};
