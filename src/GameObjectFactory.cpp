#include "GameObjectFactory.hpp"

GameObjectFactory* GameObjectFactory::Instance()
{
    static GameObjectFactory* s_pInstance = new GameObjectFactory();
    return s_pInstance;
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
    if (m_creators.find(typeID) != m_creators.end()) {
        return false;
    }

    m_creators[typeID] = pCreator;

    return true;
}

GameObject* GameObjectFactory::create(std::string typeID)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if (it == m_creators.end()) {
        std::cout << "could not find type: " << typeID << "\n";
        return NULL;
    }

    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}
