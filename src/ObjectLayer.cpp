#include "ObjectLayer.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "Vector2D.h"

ObjectLayer::~ObjectLayer() {
    for (auto &obj : m_gameObjects) {
        delete (obj);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update(Level *pLevel) {
    // iterate through the objects
    if (!m_gameObjects.empty()) {
        for (std::vector<GameObject *>::iterator it = m_gameObjects.begin();
             it != m_gameObjects.end();) // < m_gameObjects.size(); i++)
        {
            if ((*it)->getPosition().getX() <=
                TheCamera::Instance()->getPosition().m_x +
                    Game::Instance()->getGameWidth()) {
                (*it)->setUpdating(true);
                (*it)->update();
            } else {
                if ((*it)->type() != std::string("Player")) {
                    (*it)->setUpdating(false);
                } else {
                    (*it)->update();
                }
            }

            // check if dead or off screen
            if ((*it)->dead() ||
                (*it)->getPosition().m_y > Game::Instance()->getGameHeight()) {
                delete *it;
                it = m_gameObjects.erase(
                    it); // erase from vector and get new iterator
            } else {
                ++it; // increment if all ok
            }
        }
    }
}

void ObjectLayer::render() {
    for (auto &obj : m_gameObjects) {
        obj->draw();
    }
}
