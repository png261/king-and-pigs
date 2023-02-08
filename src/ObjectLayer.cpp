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
    m_collisionManager.checkPlayerEnemyCollision(
        pLevel->getPlayer(), (const std::vector<GameObject *> &)m_gameObjects);

    for (auto &obj : m_gameObjects) {
        if (obj->getPosition().getX() >
                TheCamera::Instance()->getPosition().m_x +
                    Game::Instance()->getGameWidth() &&
            obj->getPosition().getY() >
                TheCamera::Instance()->getPosition().m_y +
                    Game::Instance()->getGameHeight()) {
            obj->setUpdating(false);
            continue;
        }

        obj->setUpdating(true);
        obj->update();
    }
}

void ObjectLayer::render() {
    for (auto &obj : m_gameObjects) {
        obj->draw();
    }
}
