#include "GameObjectFactory.hpp"

#include "Log.hpp"

GameObjectFactory& GameObjectFactory::Instance()
{
    static GameObjectFactory s_instance{};
    return s_instance;
}

bool GameObjectFactory::registerType(const std::string& id, BaseCreator* const pCreator)
{
    if (m_creators.find(id) != m_creators.end()) {
        return false;
    }

    m_creators[id] = std::unique_ptr<BaseCreator>(pCreator);

    return true;
}

GameObject* GameObjectFactory::create(const std::string& id)
{
    if (m_creators.find(id) == m_creators.end()) {
        Log::warning("GameObjectFactory: could not find type " + id);
        return nullptr;
    }

    return m_creators[id]->createGameObject();
}

void GameObjectFactory::clean()
{
    m_creators.clear();
}
