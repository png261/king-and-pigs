#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <map>
#include <string>
#include "GameObject.h"

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
    ~GameObjectFactory() {}
    static GameObjectFactory* Instance();
    bool registerType(std::string typeID, BaseCreator* pCreator);
    GameObject* create(std::string typeID);

private:
    GameObjectFactory() {}

    std::map<std::string, BaseCreator*> m_creators;
};

#endif
