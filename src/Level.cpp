#include "Level.hpp"

#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

Level::Level()
{
    spawn_layer_ = std::make_unique<ObjectLayer>();
}

void Level::render() const
{
    for (const auto& layer : layers_) {
        layer->render();
    }
    spawn_layer_->render();
}

void Level::update()
{
    for (const auto& layer : layers_) {
        layer->update();
    }
    spawn_layer_->update();
}

std::vector<Tileset>* Level::getTilesets()
{
    return &tilesets_;
}

std::unordered_map<int, TileCollision>* Level::getTileCollisions()
{
    return &tiles_collision_;
}

void Level::addLayer(std::unique_ptr<Layer> layer)
{
    layers_.push_back(std::move(layer));
}

void Level::addTileSet(const Tileset tileset)
{
    tilesets_.push_back(tileset);
}

void Level::addTileCollision(const int id, const TileCollision shape)
{
    tiles_collision_[id] = shape;
}

Player* Level::getPlayer() const
{
    return player_;
}

void Level::setPlayer(Player* const player)
{
    player_ = player;
}

GameObject* Level::spawnGameObject(
    const std::string& type,
    std::unique_ptr<LoaderParams> const& params)
{
    std::unique_ptr<GameObject> pGameObject = GameObjectFactory::Instance().create(type);
    GameObject* newObject = pGameObject.get();
    pGameObject->load(std::move(params));
    spawn_layer_->addGameObject(std::move(pGameObject));
    return newObject;
}

void Level::setMapWidth(int width)
{
    map_width_ = width;
}
void Level::setMapHeight(int height)
{
    map_height_ = height;
}

int Level::getMapWidth() const
{
    return map_width_;
}

int Level::getMapHeight() const
{
    return map_height_;
}
