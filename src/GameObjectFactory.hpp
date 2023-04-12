#pragma once

#include <string>
#include <unordered_map>
#include "GameObject.hpp"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
};

template <class T = GameObject>
class Creator final : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const { return new T(); };
};

class GameObjectFactory final
{
public:
    static GameObjectFactory& Instance();
    GameObjectFactory(GameObjectFactory const&) = delete;
    GameObjectFactory& operator=(GameObjectFactory const&) = delete;

    template <class T = GameObject>
    void registerType(const std::string& id)
    {
        if (m_creators.find(id) != m_creators.end()) {
            return;
        }

        m_creators[id] = std::make_unique<Creator<T>>();
    }

    GameObject* create(const std::string& id);
    void clean();

private:
    GameObjectFactory() = default;

    std::unordered_map<std::string, std::unique_ptr<BaseCreator>> m_creators;
};
