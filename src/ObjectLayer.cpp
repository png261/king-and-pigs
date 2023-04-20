#include "ObjectLayer.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Level.hpp"

void ObjectLayer::update()
{
    for (std::size_t i = 0; i < gameObjects_.size(); ++i) {
        if (gameObjects_[i]->getPosition().x >
                Camera::Instance().getPosition().x + Game::Instance().getWindow()->getWidth() &&
            gameObjects_[i]->getPosition().y >
                Camera::Instance().getPosition().y + Game::Instance().getWindow()->getHeight()) {
            continue;
        }

        gameObjects_[i]->update();
    }

    for (auto it = gameObjects_.begin(); it != gameObjects_.end();) {
        if ((*it)->isExist()) {
            it++;
            continue;
        }

        PhysicWorld::Instance().getWorld()->DestroyBody((*it)->getBody());
        gameObjects_.erase(it);
    }
}

void ObjectLayer::render() const
{
    for (const auto& obj : gameObjects_) {
        obj->draw();
    }
}

void ObjectLayer::addGameObject(std::unique_ptr<GameObject> obj)
{
    gameObjects_.push_back(std::move(obj));
}
