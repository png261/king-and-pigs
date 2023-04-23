#pragma once

#include <tinyxml2.h>

#include "Level.hpp"

class LevelParser final
{
public:
    std::unique_ptr<Level> parseLevel(const std::string& path);

private:
    void parseTilesets(tinyxml2::XMLElement* const pTilesetRoot, Level* const pLevel) const;
    void parseObjectLayer(tinyxml2::XMLElement* const pObjectElement, Level* const pLevel) const;
    void parseTileLayer(tinyxml2::XMLElement* const pTileElement, Level* const pLevel) const;
    std::vector<std::vector<int>> parseData(const std::string& dataText) const;
    void parseCollisionObject(
        tinyxml2::XMLElement* pTilesetRoot,
        Level* const pLevel,
        const int firstGridID) const;
    std::unique_ptr<GameObject> parseObject(
        tinyxml2::XMLElement* const pObjectElement,
        Level* const pLevel) const;

    std::string getType(tinyxml2::XMLElement* const element) const;
    int getIntAttribute(tinyxml2::XMLElement* element, const char* name, int default_value = 0)
        const;
    std::string getStringAttribute(
        tinyxml2::XMLElement* element,
        const char* name,
        std::string default_value = "") const;

    int tile_size_;
    int width_;
    int height_;
};
