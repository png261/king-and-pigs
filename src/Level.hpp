#pragma once

#include <vector>
#include "Layer.hpp"
#include "Player.hpp"

class TileLayer;

struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:
    ~Level();

    void update();
    void render();

    std::vector<Tileset>* getTilesets();
    std::vector<Layer*>* getLayers();


private:
    friend class LevelParser;

    Level();
    void createTileObject();

    std::vector<Layer*> m_layers;
    std::vector<Tileset> m_tilesets;
};
