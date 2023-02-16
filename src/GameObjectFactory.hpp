#ifndef GAME_OBJECT_FACTORY_HPP
#define GAME_OBJECT_FACTORY_HPP

#include <iostream>
#include <map>
#include <string>
#include "GameObject.hpp"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

template <class T>
class Creator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const { return new T(); };
};

class GameObjectFactory
{
public:
    static GameObjectFactory* Instance()
    {
        static GameObjectFactory* s_pInstance = new GameObjectFactory();
        return s_pInstance;
    }

    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        if (m_creators.find(typeID) != m_creators.end()) {
            return false;
        }

        m_creators[typeID] = pCreator;

        return true;
    }

    GameObject* create(std::string typeID)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

        if (it == m_creators.end()) {
            std::cout << "could not find type: " << typeID << "\n";
            return NULL;
        }

        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }

private:
    GameObjectFactory() {}
    ~GameObjectFactory() {}

    std::map<std::string, BaseCreator*> m_creators;
};

#endif
