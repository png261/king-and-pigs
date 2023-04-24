#include "LevelParser.hpp"

#include <fstream>
#include <stdexcept>

#include "CONSTANT.hpp"
#include "GameObjectFactory.hpp"
#include "Layer.hpp"
#include "Level.hpp"
#include "Log.hpp"
#include "ObjectLayer.hpp"
#include "PhysicWorld.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"


std::unique_ptr<Level> LevelParser::parseLevel(const std::string& path)
{
    std::ifstream json_file(path);
    if (!json_file.is_open()) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load: ") + path);
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING err;
    if (!Json::parseFromStream(builder, json_file, &root, &err)) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load json data: ") + path);
    }

    tile_size_ = root["tilewidth"].asInt();
    width_ = root["width"].asInt();
    height_ = root["height"].asInt();

    auto level = std::make_unique<Level>();
    level->setMapWidth(width_ * tile_size_);
    level->setMapHeight(width_ * tile_size_);

    for (const auto& tileset : root["tilesets"]) {
        parseTileset(tileset, level.get());
    }

    for (const auto& layer : root["layers"]) {
        if (layer["type"].asString() == "tilelayer") {
            parseTileLayer(layer, level.get());
        } else if (layer["type"].asString() == "objectgroup") {
            parseObjectLayer(layer, level.get());
        }
    }

    return level;
}

void LevelParser::parseTileset(const Json::Value& tileset_data, Level* const level) const
{
    Tileset tileset;
    tileset.name = tileset_data["name"].asString();
    tileset.first_grid_id = tileset_data["firstgid"].asInt();
    tileset.spacing = tileset_data["spacing"].asInt();
    tileset.margin = tileset_data["margin"].asInt();
    tileset.columns = tileset_data["columns"].asInt();

    TextureManager::Instance().load(
        LEVEL_DIRECTORY + tileset_data["image"].asString(),
        tileset.name);
    level->addTileSet(tileset);

    for (const auto& tile : tileset_data["tiles"]) {
        const int id = tile["id"].asInt() + tileset.first_grid_id;
        const bool is_one_way = tile["type"].asString() == std::string("oneway");
        const int width = tile["objectgroup"]["objects"][0]["width"].asInt();
        const int height = tile["objectgroup"]["objects"][0]["height"].asInt();
        level->addTileCollision(id, {is_one_way, width, height});
    }
}

std::unique_ptr<GameObject> LevelParser::parseObject(
    const Json::Value& object_data,
    Level* const level) const
{
    std::string type = object_data["type"].asString();

    std::unique_ptr<GameObject> object = GameObjectFactory::Instance().create(type);
    if (object == nullptr) {
        return nullptr;
    }

    object->load(std::make_unique<LoaderParams>(LoaderParams(
        object_data["x"].asInt(),
        object_data["y"].asInt(),
        object_data["width"].asInt(),
        object_data["height"].asInt())));

    if (type == "Player") {
        level->setPlayer(dynamic_cast<Player*>(object.get()));
    }

    return object;
}

void LevelParser::parseObjectLayer(const Json::Value& layer, Level* const level) const
{
    auto object_layer = std::make_unique<ObjectLayer>();

    bool is_empty = true;
    for (auto& object : layer["objects"]) {
        std::unique_ptr<GameObject> obj = parseObject(object, level);
        if (obj != nullptr) {
            is_empty = false;
            object_layer->addGameObject(std::move(obj));
        }
    }

    if (!is_empty) {
        level->addLayer(std::move(object_layer));
    }
}

void LevelParser::parseTileLayer(const Json::Value& layer, Level* const level) const
{
    auto tile_layer =
        std::make_unique<TileLayer>(tile_size_, width_, height_, *level->getTilesets());

    std::vector<int> data;
    for (const auto& id : layer["data"]) {
        data.push_back(id.asInt());
    }

    tile_layer->setTileData(data);
    level->addLayer(std::move(tile_layer));

    std::unordered_map<int, TileCollision>* collision_shape = level->getTileCollisions();
    if (!collision_shape->empty()) {
        for (int row = 0; row < height_; ++row) {
            for (int col = 0; col < width_; ++col) {
                const int id = data[row * width_ + col];
                if (id == 0) {
                    continue;
                }
                std::unordered_map<int, TileCollision>::iterator it = collision_shape->find(id);
                if (it == collision_shape->end()) {
                    continue;
                }
                const TileCollision shape = it->second;

                PhysicWorld::Instance().createStaticBody(
                    tile_size_ * b2Vec2(col, row),
                    shape.width,
                    shape.height,
                    shape.is_one_way ? PhysicWorld::CAT_ONE_WAY_WALL : PhysicWorld::CAT_WALL,
                    PhysicWorld::MASK_WALL);
            }
        }
    }
}
