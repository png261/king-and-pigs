#include "ObjectLayer.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "Log.hpp"

ObjectLayer::~ObjectLayer()
{
    for (auto& obj : m_gameObjects) {
        delete (obj);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update()
{
    for (auto& obj : m_gameObjects) {
        if (obj->getPosition().x >
                Camera::Instance()->getPosition().x + Game::Instance()->getWindow()->getWidth() &&
            obj->getPosition().y >
                Camera::Instance()->getPosition().y + Game::Instance()->getWindow()->getHeight()) {
            obj->setUpdating(false);
            continue;
        }

        obj->setUpdating(true);
        obj->update();
    }

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
        if ((*it)->isExist() == false) {
            PhysicWorld::Instance()->getWorld()->DestroyBody((*it)->getBody());
            delete (*it);
            m_gameObjects.erase(it);
            continue;
        }
        it++;
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

void ObjectLayer::addGameObject(GameObject* obj)
{
    m_gameObjects.push_back(obj);
}
