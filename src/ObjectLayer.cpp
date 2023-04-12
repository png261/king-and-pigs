#include "ObjectLayer.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Level.hpp"

void ObjectLayer::update()
{
    for (std::size_t i = 0; i < m_gameObjects.size(); i++) {
        if (m_gameObjects[i]->getPosition().x >
                Camera::Instance().getPosition().x + Game::Instance().getWindow()->getWidth() &&
            m_gameObjects[i]->getPosition().y >
                Camera::Instance().getPosition().y + Game::Instance().getWindow()->getHeight()) {
            continue;
        }

        m_gameObjects[i]->update();
    }

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
        if ((*it)->isExist()) {
            it++;
            continue;
        }

        PhysicWorld::Instance().getWorld()->DestroyBody((*it)->getBody());
        m_gameObjects.erase(it);
    }
}

void ObjectLayer::render() const
{
    for (const auto& obj : m_gameObjects) {
        obj->draw();
    }
}

void ObjectLayer::addGameObject(GameObject* obj)
{
    m_gameObjects.push_back(std::unique_ptr<GameObject>(obj));
}
