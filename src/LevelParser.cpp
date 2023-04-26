#include "LevelParser.hpp"

#include <tinyxml2.h>
#include <fstream>
#include <iostream>
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
#include "Utils.hpp"


using namespace tinyxml2;
std::unique_ptr<Level> LevelParser::parseLevel(const std::string& path)
{
    std::ifstream json_file(path);
    if (!json_file.is_open()) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load: ") + path);
    }

    Json::Value map;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING err;
    if (!Json::parseFromStream(builder, json_file, &map, &err)) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load json data: ") + path);
    }

    tile_size_ = map["tilewidth"].asInt();
    width_ = map["width"].asInt();
    height_ = map["height"].asInt();

    auto level = std::make_unique<Level>(
        width_ * tile_size_,
        height_ * tile_size_,
        Utils::hexToRgba(map["backgroundcolor"].asString()));

    for (const auto& tileset : map["tilesets"]) {
        loadTileset(tileset, level.get());
    }

    for (const auto& layer : map["layers"]) {
        if (layer["type"].asString() == "tilelayer") {
            parseTileLayer(layer, level.get());
        } else if (layer["type"].asString() == "objectgroup") {
            parseObjectLayer(layer, level.get());
        }
    }

    return level;
}

void LevelParser::loadTileset(const Json::Value& tileset_data, Level* const level) const
{
    if (!tileset_data.isMember("image")) {
        return;
    }

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
    std::string type = "";
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    if (object_data.isMember("template")) {
        x = object_data["x"].asInt();
        y = object_data["y"].asInt();
        const std::string templatePath = LEVEL_DIRECTORY + object_data["template"].asString();
        XMLDocument document;
        if (document.LoadFile(templatePath.c_str()) != XML_SUCCESS) {
            throw std::runtime_error(
                "LevelParser: " + std::string("fail to load template object: ") + templatePath);
        }

        XMLElement* const root = document.RootElement();
        for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("object")) {
                type = e->Attribute("type");
                w = std::stoi(e->Attribute("width"));
                h = std::stoi(e->Attribute("height"));
            }
        }
        y -= h;
    } else {
        type = object_data["type"].asString();
        x = object_data["x"].asInt();
        y = object_data["y"].asInt();
        w = object_data["width"].asInt();
        h = object_data["height"].asInt();
    }

    std::unique_ptr<GameObject> object = GameObjectFactory::Instance().create(type);
    if (object == nullptr) {
        return nullptr;
    }

    object->load(std::make_unique<LoaderParams>(LoaderParams(x, y, w, h)));

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
