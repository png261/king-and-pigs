#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
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

    std::vector<Tileset>* getTilesets() { return &m_tilesets; }
    std::vector<Layer*>* getLayers() { return &m_layers; }
    std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }

    std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }


private:
    friend class LevelParser;

    Level();

    std::vector<Layer*> m_layers;
    std::vector<Tileset> m_tilesets;
    std::vector<TileLayer*> m_collisionLayers;
};

#endif
