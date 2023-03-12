#pragma once

#include <map>
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

struct CollisionShape
{
    int width;
    int height;
};

class Level
{
public:
    ~Level();

    void update();
    void render();

    std::vector<Tileset>* getTilesets();
    std::map<int, CollisionShape>* getCollisionShapes();
    std::vector<Layer*>* getLayers();


private:
    friend class LevelParser;

    Level();
    void createTileObject();

    std::vector<Layer*> m_layers;
    std::map<int, CollisionShape> m_collisionShapes;
    std::vector<Tileset> m_tilesets;
};
