#include "LevelParser.hpp"
#include <nlohmann/json.hpp>

#include <tinyxml2.h>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "CONSTANT.hpp"
#include "Layer.hpp"
#include "Level.hpp"
#include "ObjectFactory.hpp"
#include "ObjectLayer.hpp"
#include "PhysicManager.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"
#include "Utils.hpp"

std::unique_ptr<Level> LevelParser::parseLevel(const std::string& path)
{
    const nlohmann::json& map = Utils::read_json_file(path);
    tile_size_ = map["tilewidth"].get<int>();
    width_ = map["width"].get<int>();
    height_ = map["height"].get<int>();

    auto level = std::make_unique<Level>(
        width_ * tile_size_,
        height_ * tile_size_,
        Utils::hexToRgba(map["backgroundcolor"].get<std::string>()));

    for (const auto& tileset : map["tilesets"]) {
        loadTileset(tileset, level.get());
    }

    for (const auto& layer : map["layers"]) {
        if (layer["type"].get<std::string>() == "tilelayer") {
            parseTileLayer(layer, level.get());
        } else if (layer["type"].get<std::string>() == "objectgroup") {
            parseObjectLayer(layer, level.get());
        }
    }

    return level;
}

void LevelParser::loadTileset(const nlohmann::json& tileset_data, Level* const level) const
{
    if (!tileset_data.contains("image")) {
        return;
    }

    Tileset tileset;
    tileset.name = tileset_data["name"].get<std::string>();
    tileset.first_grid_id = tileset_data["firstgid"].get<int>();
    tileset.spacing = tileset_data["spacing"].get<int>();
    tileset.margin = tileset_data["margin"].get<int>();
    tileset.columns = tileset_data["columns"].get<int>();

    TextureManager::Instance().load(
        LEVEL_DIRECTORY + tileset_data["image"].get<std::string>(),
        tileset.name);
    level->addTileSet(tileset);

    for (const auto& tile : tileset_data["tiles"]) {
        const int id = tile["id"].get<int>() + tileset.first_grid_id;
        const bool is_one_way =
            tile.contains("type") && (tile["type"].get<std::string>() == ONE_WAY_TYPE);
        const int width = tile["objectgroup"]["objects"][0]["width"].get<int>();
        const int height = tile["objectgroup"]["objects"][0]["height"].get<int>();
        level->addTileCollision(id, {is_one_way, width, height});
    }
}

std::unique_ptr<Object> LevelParser::parseObject(
    const nlohmann::json& object_data,
    Level* const level) const
{
    std::string type = "";
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    if (object_data.contains("template")) {
        x = object_data["x"].get<int>();
        y = object_data["y"].get<int>();
        const std::string templatePath =
            LEVEL_DIRECTORY + object_data["template"].get<std::string>();
        tinyxml2::XMLDocument document;
        if (document.LoadFile(templatePath.c_str()) != tinyxml2::XML_SUCCESS) {
            throw std::runtime_error(
                "LevelParser: " + std::string("fail to load template object: ") + templatePath);
        }

        tinyxml2::XMLElement* const root = document.RootElement();
        for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr;
             e = e->NextSiblingElement()) {
            if (e->Value() == std::string("object")) {
                type = e->Attribute("type");
                w = std::stoi(e->Attribute("width"));
                h = std::stoi(e->Attribute("height"));
            }
        }
        y -= h;
    } else {
        type = object_data["type"].get<std::string>();
        x = object_data["x"].get<int>();
        y = object_data["y"].get<int>();
        w = object_data["width"].get<int>();
        h = object_data["height"].get<int>();
    }

    std::unique_ptr<Object> object = ObjectFactory::Instance().create(type);
    if (object == nullptr) {
        return nullptr;
    }

    object->load(LoaderParams(x, y, w, h));

    if (type == "Player") {
        level->setPlayer(dynamic_cast<Player*>(object.get()));
    }

    return object;
}

void LevelParser::parseObjectLayer(const nlohmann::json& layer, Level* const level) const
{
    auto object_layer = std::make_unique<ObjectLayer>();

    bool is_empty = true;
    for (auto& object : layer["objects"]) {
        std::unique_ptr<Object> obj = parseObject(object, level);
        if (obj != nullptr) {
            is_empty = false;
            object_layer->addObject(std::move(obj));
        }
    }

    if (!is_empty) {
        level->addLayer(std::move(object_layer));
    }
}

void LevelParser::parseTileLayer(const nlohmann::json& layer, Level* const level) const
{
    auto tile_layer =
        std::make_unique<TileLayer>(tile_size_, width_, height_, *level->getTilesets());

    auto data = layer["data"].get<std::vector<int>>();

    tile_layer->setTileData(data);
    level->addLayer(std::move(tile_layer));

    std::unordered_map<int, TileCollision>* tile_collisions = level->getTileCollisions();
    if (tile_collisions->empty()) {
        return;
    }

    for (int row = 0; row < height_; ++row) {
        for (int col = 0; col < width_; ++col) {
            const int id = data[row * width_ + col];
            if (id == 0) {
                continue;
            }
            std::unordered_map<int, TileCollision>::iterator it = tile_collisions->find(id);
            if (it == tile_collisions->end()) {
                continue;
            }
            const TileCollision shape = it->second;

            PhysicManager::Instance().createStaticBody(
                tile_size_ * b2Vec2(col, row),
                shape.width,
                shape.height,
                shape.is_one_way ? ContactCategory::CAT_ONE_WAY_WALL : ContactCategory::CAT_WALL,
                ContactMask::MASK_WALL);
        }
    }
}
