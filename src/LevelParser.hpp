#pragma once

#include <tinyxml2.h>
#include "Level.hpp"

class LevelParser final
{
public:
    std::shared_ptr<Level> parseLevel(const char* levelFile);

private:
    void parseTilesets(tinyxml2::XMLElement* const pTilesetRoot, std::shared_ptr<Level> pLevel);
    void parseObjectLayer(
        tinyxml2::XMLElement* const pObjectElement,
        std::shared_ptr<Level> const pLevel);
    void parseTileLayer(tinyxml2::XMLElement* const pTileElement, std::shared_ptr<Level> pLevel);
    std::vector<std::vector<int>> parseData(const std::string& dataText);
    void parseCollisionObject(
        tinyxml2::XMLElement* pTilesetRoot,
        std::shared_ptr<Level> pLevel,
        int firstGridID);
    GameObject* parseObject(
        tinyxml2::XMLElement* const pObjectElement,
        std::shared_ptr<Level> const pLevel);
    std::string getType(tinyxml2::XMLElement* const element);

    int m_tileSize;
    int m_width;
    int m_height;
};
