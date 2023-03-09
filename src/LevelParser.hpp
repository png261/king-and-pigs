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
        std::vector<Tileset>* const pTilesets);
    void parseObjectLayer(
        tinyxml2::XMLElement* const pObjectElement,
        std::vector<Layer*>* const pLayers,
        Level* const pLevel);
    void parseTileLayer(
        tinyxml2::XMLElement* const pTileElement,
        std::vector<Layer*>* const pLayers,
        std::vector<Tileset>* const pTilesets);

    int m_tileSize;
    int m_width;
    int m_height;
};
