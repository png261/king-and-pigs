#pragma once

#include "Level.hpp"
#include "tinyxml2.h"

class LevelParser final
{
public:
    Level* parseLevel(const char* levelFile);

private:
    void parseTextures(tinyxml2::XMLElement* const pTextureRoot);
    void parseTilesets(
        tinyxml2::XMLElement* const pTilesetRoot,
        std::vector<Tileset>* const pTilesets,
        std::map<int, CollisionShape>* const pCollisionShapes);
    void parseObjectLayer(
        tinyxml2::XMLElement* const pObjectElement,
        std::vector<Layer*>* const pLayers,
        Level* const pLevel);
    void parseTileLayer(
        tinyxml2::XMLElement* const pTileElement,
        std::vector<Layer*>* const pLayers,
        std::vector<Tileset>* const pTilesets,
        std::map<int, CollisionShape>* const pCollisionShape);
    std::vector<std::vector<int>> parseData(const std::string dataText);
    void parseCollisionObject(
        tinyxml2::XMLElement* pTilesetRoot,
        int firstGridID,
        std::map<int, CollisionShape>* pCollisionShapes);

    int m_tileSize;
    int m_width;
    int m_height;
};
