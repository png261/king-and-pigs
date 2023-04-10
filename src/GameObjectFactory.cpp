#include "GameObjectFactory.hpp"

#include "Log.hpp"

GameObjectFactory& GameObjectFactory::Instance()
{
    static GameObjectFactory s_instance{}; 
    return s_instance;
}

bool GameObjectFactory::registerType(const std::string typeID, BaseCreator* const pCreator)
{
    if (m_creators.find(typeID) != m_creators.end()) {
        return false;
    }

    m_creators[typeID] = std::unique_ptr<BaseCreator>(pCreator);

    return true;
}

GameObject* GameObjectFactory::create(const std::string typeID)
{
    std::unordered_map<std::string, std::unique_ptr<BaseCreator>>::iterator it =
        m_creators.find(typeID);

    if (it == m_creators.end()) {
        Log::warning("could not find type: " + typeID);
        return nullptr;
    }

    return it->second->createGameObject();
}

void GameObjectFactory::clean()
{
    m_creators.clear();
}
