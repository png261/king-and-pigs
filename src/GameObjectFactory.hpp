#ifndef GAME_OBJECT_FACTORY_HPP
#define GAME_OBJECT_FACTORY_HPP

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
    static GameObjectFactory* Instance();
    bool registerType(std::string typeID, BaseCreator* pCreator);
    GameObject* create(std::string typeID);

private:
    GameObjectFactory() {}
    ~GameObjectFactory() {}

    std::map<std::string, BaseCreator*> m_creators;
};

#endif
