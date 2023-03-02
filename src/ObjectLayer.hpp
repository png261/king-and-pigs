#ifndef OBJECT_LAYER_HPP
#define OBJECT_LAYER_HPP

#include <vector>
#include "Layer.hpp"

class GameObject;

class ObjectLayer : public Layer
{
public:
    virtual ~ObjectLayer();

    virtual void update(Level* const pLevel);
    virtual void render();

    std::vector<GameObject*>* getGameObjects();

private:
    std::vector<GameObject*> m_gameObjects;
};

#endif
