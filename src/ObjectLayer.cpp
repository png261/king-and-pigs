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

void ObjectLayer::update()
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
        if ((*it)->isExist() == false) {
            PhysicWorld::Instance()->getWorld()->DestroyBody((*it)->getBody());
            delete (*it);
            m_gameObjects.erase(it);
            it--;
            continue;
        }

        if ((*it)->getPosition().x >
                Camera::Instance()->getPosition().x + Game::Instance()->getWindow()->getWidth() &&
            (*it)->getPosition().y >
                Camera::Instance()->getPosition().y + Game::Instance()->getWindow()->getHeight()) {
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
