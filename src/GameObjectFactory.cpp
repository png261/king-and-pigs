#include "GameObjectFactory.hpp"

#include "Log.hpp"

GameObjectFactory& GameObjectFactory::Instance()
{
    static GameObjectFactory instance{};
    return instance;
}

void GameObjectFactory::registerType(const std::string& id, std::unique_ptr<BaseCreator> creator)
{
    if (creators_.find(id) != creators_.end()) {
        return;
    }

    creators_[id] = std::move(creator);
}

std::unique_ptr<GameObject> GameObjectFactory::create(const std::string& id)
{
    if (creators_.find(id) == creators_.end()) {
        Log::warning("GameObjectFactory: could not find type " + id);
        return nullptr;
    }

    return creators_[id]->create();
}

void GameObjectFactory::clean()
{
    creators_.clear();
}
