#include "ObjectFactory.hpp"

#include "Log.hpp"

ObjectFactory& ObjectFactory::Instance()
{
    static ObjectFactory instance{};
    return instance;
}

void ObjectFactory::registerType(const std::string& id, std::unique_ptr<BaseCreator> creator)
{
    if (creators_.find(id) != creators_.end()) {
        return;
    }

    creators_[id] = std::move(creator);
}

std::unique_ptr<Object> ObjectFactory::create(const std::string& id) const
{
    if (creators_.find(id) == creators_.end()) {
        Log::warning("ObjectFactory: could not find type " + id);
        return nullptr;
    }

    return creators_.at(id)->create();
}

void ObjectFactory::clean()
{
    creators_.clear();
}
