#include "ObjectLayer.hpp"

#include "Camera.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "Level.hpp"

ObjectLayer::~ObjectLayer()
{
    for (auto& obj : m_gameObjects) {
        delete (obj);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
        if ((*it)->isDead()) {
            delete (*it);
            m_gameObjects.erase(it);
            it--;
            continue;
        }

        if ((*it)->getPosition().x >
                TheCamera::Instance()->getPosition().x + Game::Instance()->getGameWidth() &&
            (*it)->getPosition().y >
                TheCamera::Instance()->getPosition().y + Game::Instance()->getGameHeight()) {
            (*it)->setUpdating(false);
            continue;
        }


        (*it)->setUpdating(true);
        (*it)->update();
    }
}

void ObjectLayer::render()
{
    for (auto& obj : m_gameObjects) {
        obj->draw();
    }
}


std::vector<GameObject*>* ObjectLayer::getGameObjects()
{
    return &m_gameObjects;
}
