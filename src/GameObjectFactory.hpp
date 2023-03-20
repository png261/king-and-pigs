#pragma once

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

class GameObjectFactory final
{
public:
    static GameObjectFactory* Instance();
    bool registerType(const std::string typeID, BaseCreator* const pCreator);
    GameObject* create(const std::string typeID);

private:
    GameObjectFactory() {}
    ~GameObjectFactory() {}

    std::map<std::string, BaseCreator*> m_creators;
};
