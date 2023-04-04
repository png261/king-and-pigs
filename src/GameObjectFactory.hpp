#pragma once

#include <string>
#include <unordered_map>
#include "GameObject.hpp"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() = default;
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
    static std::shared_ptr<GameObjectFactory> Instance();
    GameObjectFactory(GameObjectFactory const&) = delete;
    GameObjectFactory& operator=(GameObjectFactory const&) = delete;

    bool registerType(const std::string typeID, BaseCreator* const pCreator);
    GameObject* create(const std::string typeID);
    void clean();

private:
    GameObjectFactory() = default;

    std::unordered_map<std::string, BaseCreator*> m_creators;
};
