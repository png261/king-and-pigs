#pragma once

#include <string>
#include <unordered_map>

#include "GameObject.hpp"

class BaseCreator
{
public:
    virtual std::unique_ptr<GameObject> create() const = 0;
};

class GameObjectFactory final
{
public:
    static GameObjectFactory& Instance();
    GameObjectFactory(GameObjectFactory const&) = delete;
    GameObjectFactory& operator=(GameObjectFactory const&) = delete;

    void registerType(const std::string& id, std::unique_ptr<BaseCreator> creator);
    std::unique_ptr<GameObject> create(const std::string& id) const;
    void clean();

private:
    GameObjectFactory() = default;

    std::unordered_map<std::string, std::unique_ptr<BaseCreator>> creators_;
};
