#include "ObjectLayer.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Level.hpp"

void ObjectLayer::update()
{
    for (const auto& object : objects_) {
        const bool is_in_view =
            object->getX() <=
                Camera::Instance().getX() + Game::Instance().getWindow()->getWidth() &&
            object->getY() <= Camera::Instance().getY() + Game::Instance().getWindow()->getHeight();

        if (!is_in_view) {
            continue;
        }

        object->update();
    }

    for (auto it = objects_.begin(); it != objects_.end();) {
        if ((*it)->isExist()) {
            it++;
            continue;
        }

        const auto object = dynamic_cast<PhysicObject*>(it->get());
        PhysicManager::Instance().getWorld()->DestroyBody(object->getBody());
        objects_.erase(it);
    }
}

void ObjectLayer::render() const
{
    for (const auto& obj : objects_) {
        obj->draw();
    }
}

void ObjectLayer::addObject(std::unique_ptr<Object> object)
{
    objects_.push_back(std::move(object));
}
