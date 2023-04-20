#pragma once

#include <memory>
#include <vector>
#include "Layer.hpp"

class GameObject;

class ObjectLayer final : public Layer
{
public:
    void update();
    void render() const;

    std::vector<std::unique_ptr<GameObject>>* getGameObjects();
    void addGameObject(std::unique_ptr<GameObject> object);

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects_;
};
