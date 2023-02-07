#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "Level.h"
#include "tinyxml2.h"

class LevelParser {
  public:
    Level *parseLevel(const char *levelFile);

  private:
    void parseTextures(tinyxml2::XMLElement *pTextureRoot);
    void parseTilesets(tinyxml2::XMLElement *pTilesetRoot,
                       std::vector<Tileset> *pTilesets);
    void parseObjectLayer(tinyxml2::XMLElement *pObjectElement,
                          std::vector<Layer *> *pLayers, Level *pLevel);
    void parseTileLayer(tinyxml2::XMLElement *pTileElement,
                        std::vector<Layer *> *pLayers,
                        const std::vector<Tileset> *pTilesets, std::vector<TileLayer *> *pCollisionLayers);
    int m_tileSize;
    int m_width;
    int m_height;
};

#endif
