#include "ObjectLayer.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Level.hpp"

void ObjectLayer::update()
{
    for (const auto& object : objects_) {
        if (object->getPosition().x >
                Camera::Instance().getPosition().x + Game::Instance().getWindow()->getWidth() &&
            object->getPosition().y >
                Camera::Instance().getPosition().y + Game::Instance().getWindow()->getHeight()) {
            continue;
        }

        object->update();
    }

    for (auto it = objects_.begin(); it != objects_.end();) {
        if ((*it)->isExist()) {
            it++;
            continue;
        }

        auto object = dynamic_cast<PhysicObject*>(it->get());
        PhysicWorld::Instance().getWorld()->DestroyBody(object->getBody());
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
