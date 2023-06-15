#pragma once

#include <string>
#include <unordered_map>

#include "Object.hpp"

class BaseCreator
{
public:
    virtual std::unique_ptr<Object> create() const = 0;
};

class ObjectFactory final
{
public:
    static ObjectFactory& Instance();
    ObjectFactory(ObjectFactory const&) = delete;
    ObjectFactory& operator=(ObjectFactory const&) = delete;

    void registerType(const std::string& id, std::unique_ptr<BaseCreator> creator);
    std::unique_ptr<Object> create(const std::string& id) const;
    void clean();

private:
    ObjectFactory() = default;

    std::unordered_map<std::string, std::unique_ptr<BaseCreator>> creators_;
};
