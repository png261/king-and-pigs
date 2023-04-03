#pragma once

#include <unordered_map>
#include <vector>
#include "Layer.hpp"
#include "ObjectLayer.hpp"
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
    bool isOneWay;
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
    std::unordered_map<int, CollisionShape>* getCollisionShapes();
    std::vector<Layer*>* getLayers();
    void addLayer(Layer*);
    void addTileSet(Tileset tileset);
    void addCollisionShape(std::pair<int, CollisionShape> shape);

    Player* getPlayer();
    void setPlayer(Player* player);
    GameObject* spawnGameObject(std::string type, std::unique_ptr<LoaderParams> const& pParams);

private:
    friend class LevelParser;

    Level();
    void createTileObject();
    Player* m_pPlayer;

    ObjectLayer* m_spawnLayer;
    std::vector<Layer*> m_layers;
    std::unordered_map<int, CollisionShape> m_collisionShapes;
    std::vector<Tileset> m_tilesets;
};
