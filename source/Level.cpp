#include "Level.hpp"

#include "Game.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "ObjectFactory.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

Level::Level()
    : spawn_layer_(std::make_unique<ObjectLayer>())
{}

Level::Level(const int width, const int height, const Color& background)
    : width_(width)
    , height_(height)
    , background_color_(background)
    , spawn_layer_(std::make_unique<ObjectLayer>())
{}


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

void Level::addTileSet(const Tileset& tileset)
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

Object* Level::spawnObject(const std::string& type, const LoaderParams& params)
    const
{
    std::unique_ptr<Object> object = ObjectFactory::Instance().create(type);
    Object* newObject = object.get();
    object->load(params);
    spawn_layer_->addObject(std::move(object));
    return newObject;
}

int Level::getMapWidth() const
{
    return width_;
}

int Level::getMapHeight() const
{
    return height_;
}

Color Level::getBackgroundColor() const
{
    return background_color_;
}
