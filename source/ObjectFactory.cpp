#include "ObjectFactory.hpp"

#include <stdexcept>

#include "Log.hpp"

ObjectFactory& ObjectFactory::Instance()
{
    static ObjectFactory instance{};
    return instance;
}

void ObjectFactory::registerType(const std::string& id, std::unique_ptr<BaseCreator> creator)
{
    if (creators_.count(id) != 0) {
        return;
    }

    creators_[id] = std::move(creator);
}

std::unique_ptr<Object> ObjectFactory::create(const std::string& id) const
{
    try {
        return creators_.at(id)->create();
    } catch (const std::out_of_range& oor) {
        Log::warning("ObjectFactory: could not find type " + id);
        return nullptr;
    }
}

void ObjectFactory::clean()
{
    creators_.clear();
}
