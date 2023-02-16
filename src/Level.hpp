#ifndef LEVEL_HPP
#define LEVEL_HPP

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
    std::vector<TileLayer*>* getCollisionLayers();
    std::vector<TileLayer*>& getCollidableLayers();


private:
    friend class LevelParser;

    Level();

    std::vector<Layer*> m_layers;
    std::vector<Tileset> m_tilesets;
    std::vector<TileLayer*> m_collisionLayers;
};

#endif
