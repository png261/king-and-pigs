#pragma once

#include <unordered_map>
#include <vector>
#include "Layer.hpp"
#include "ObjectLayer.hpp"
#include "Player.hpp"

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

class Level final
{
public:
    ~Level();
    Level();

    void update();
    void render() const;

    std::vector<Tileset>* getTilesets();
    std::unordered_map<int, CollisionShape>* getCollisionShapes();
    void addLayer(std::shared_ptr<Layer> const& layer);
    void addTileSet(const Tileset tileset);
    void addCollisionShape(const int id, const CollisionShape shape);

    Player* getPlayer() const;
    void setPlayer(Player* const player);
    GameObject* spawnGameObject(
        const std::string type,
        std::unique_ptr<LoaderParams> const& pParams);

private:
    friend class LevelParser;

    void createTileObject();
    Player* m_pPlayer;

    std::unique_ptr<ObjectLayer> m_spawnLayer;
    std::vector<std::shared_ptr<Layer>> m_layers;
    std::vector<Tileset> m_tilesets;
    std::unordered_map<int, CollisionShape> m_collisionShapes;
};
