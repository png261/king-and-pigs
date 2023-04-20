#pragma once

#include <unordered_map>
#include <vector>
#include "Layer.hpp"
#include "ObjectLayer.hpp"
#include "Player.hpp"

struct Tileset
{
    int first_grid_id;
    int tile_width;
    int tile_height;
    int spacing;
    int margin;
    int width;
    int height;
    int columns;
    std::string name;
};

struct CollisionShape
{
    bool is_one_way;
    int width;
    int height;
};

class Level final
{
public:
    Level();

    void update();
    void render() const;

    std::vector<Tileset>* getTilesets();
    std::unordered_map<int, CollisionShape>* getCollisionShapes();
    void addLayer(std::unique_ptr<Layer> layer);
    void addTileSet(const Tileset tileset);
    void addCollisionShape(const int id, const CollisionShape shape);

    Player* getPlayer() const;
    void setPlayer(Player* const player);
    GameObject* spawnGameObject(
        const std::string& type,
        std::unique_ptr<LoaderParams> const& params);
    void setMapWidth(int width);
    void setMapHeight(int height);

    int getMapWidth() const;
    int getMapHeight() const;

private:
    friend class LevelParser;

    void createTileObject();
    Player* player_;
    int map_width_;
    int map_height_;

    std::unique_ptr<ObjectLayer> spawn_layer_;
    std::vector<std::unique_ptr<Layer>> layers_;
    std::vector<Tileset> tilesets_;
    std::unordered_map<int, CollisionShape> collision_shapes_;
};
