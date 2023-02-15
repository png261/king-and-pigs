#include "ObjectLayer.h"
#include <iostream>

#include "Camera.h"
#include "Collision.h"
#include "Enemy.h"
#include "Game.h"
#include "Level.h"

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

        if ((*it)->getPosition().getX() >
                TheCamera::Instance()->getPosition().m_x + Game::Instance()->getGameWidth() &&
            (*it)->getPosition().getY() >
                TheCamera::Instance()->getPosition().m_y + Game::Instance()->getGameHeight()) {
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
