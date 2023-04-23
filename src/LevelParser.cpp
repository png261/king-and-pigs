#include "LevelParser.hpp"

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

using namespace tinyxml2;

std::unique_ptr<Level> LevelParser::parseLevel(const std::string& path)
{
    XMLDocument document;
    if (document.LoadFile(path.c_str()) != XML_SUCCESS) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load: ") + path);
    }

    XMLElement* const root = document.RootElement();
    if (root == nullptr) {
        Log::error(std::string(path) + ": missing  root element");
    }

    tile_size_ = getIntAttribute(root, "tilewidth");
    width_ = getIntAttribute(root, "width");
    height_ = getIntAttribute(root, "height");

    auto level = std::make_unique<Level>();
    level->setMapWidth(width_ * tile_size_);
    level->setMapHeight(width_ * tile_size_);

    for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, level.get());
        }

        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            bool is_tile_layer =
                e->FirstChildElement()->Value() == std::string("data") ||
                (e->FirstChildElement()->NextSiblingElement() != 0 &&
                 e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"));
            bool is_object_layer = e->FirstChildElement()->Value() == std::string("object");

            if (is_object_layer) {
                parseObjectLayer(e, level.get());
            } else if (is_tile_layer) {
                parseTileLayer(e, level.get());
            }
        }
    }

    return level;
}

void LevelParser::parseTilesets(XMLElement* const tileset_root, Level* const level) const
{
    XMLElement* const image = tileset_root->FirstChildElement();

    Tileset tileset;

    tileset.width = getIntAttribute(image, "width");
    tileset.height = getIntAttribute(image, "height");
    tileset.first_grid_id = getIntAttribute(tileset_root, "firstgid");
    tileset.tile_width = getIntAttribute(tileset_root, "tilewidth");
    tileset.tile_height = getIntAttribute(tileset_root, "tileheight");
    tileset.spacing = getIntAttribute(tileset_root, "spacing");
    tileset.margin = getIntAttribute(tileset_root, "margin");
    tileset.name = getStringAttribute(tileset_root, "name");

    tileset.columns = tileset.width / (tileset.tile_width + tileset.spacing);

    TextureManager::Instance().load(LEVEL_DIRECTORY + image->Attribute("source"), tileset.name);
    level->addTileSet(tileset);
    parseCollisionObject(tileset_root, level, tileset.first_grid_id);
}

void LevelParser::parseCollisionObject(
    XMLElement* tileset_root,
    Level* const level,
    const int first_grid_id) const
{
    for (XMLElement* e = tileset_root->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tile")) {
            XMLElement* const obj = e->FirstChildElement()->FirstChildElement();
            int id = getIntAttribute(e, "id") + first_grid_id;
            bool is_one_way = getType(e) == std::string("oneway");

            int width = getIntAttribute(obj, "width");
            int height = getIntAttribute(obj, "height");
            level->addCollisionShape(id, {is_one_way, width, height});
        }
    }
}

std::unique_ptr<GameObject> LevelParser::parseObject(XMLElement* const element, Level* const level)
    const
{
    int x = getIntAttribute(element, "x");
    int y = getIntAttribute(element, "y");
    int width = getIntAttribute(element, "width");
    int height = getIntAttribute(element, "height");
    std::string type = getType(element);

    std::unique_ptr<GameObject> object = GameObjectFactory::Instance().create(type);
    if (object == nullptr) {
        return nullptr;
    }

    object->load(std::make_unique<LoaderParams>(LoaderParams(x, y, width, height)));

    if (type == "Player") {
        level->setPlayer(dynamic_cast<Player*>(object.get()));
    }

    return object;
}

void LevelParser::parseObjectLayer(XMLElement* const root, Level* const level) const
{
    auto object_layer = std::make_unique<ObjectLayer>();

    bool is_empty = true;
    for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {
            std::unique_ptr<GameObject> obj = parseObject(e, level);
            if (obj != nullptr) {
                is_empty = false;
                object_layer->addGameObject(std::move(obj));
            }
        }
    }

    if (!is_empty) {
        level->addLayer(std::move(object_layer));
    }
}

std::vector<std::vector<int>> LevelParser::parseData(const std::string& dataText) const
{
    std::vector<std::vector<int>> result;
    std::vector<int> empty_row(width_);
    for (int i = 0; i < height_; ++i) {
        result.push_back(empty_row);
    }

    int start = 0;
    for (auto& row : result) {
        for (auto& col : row) {
            int end = dataText.find(',', start);
            col = std::stoi(dataText.substr(start, end - start));
            start = end + 1;
        }
    }

    return result;
}

void LevelParser::parseTileLayer(XMLElement* const tile_element, Level* const level) const
{
    auto tile_layer =
        std::make_unique<TileLayer>(tile_size_, width_, height_, *level->getTilesets());

    std::vector<std::vector<int>> ids;
    for (XMLElement* e = tile_element->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            ids = parseData(e->GetText());
        }
    }

    tile_layer->setTileIDs(ids);
    level->addLayer(std::move(tile_layer));

    std::unordered_map<int, CollisionShape>* collision_shape = level->getCollisionShapes();
    if (!collision_shape->empty()) {
        for (int row = 0; row < height_; row++) {
            for (int col = 0; col < width_; col++) {
                int id = ids[row][col];
                if (id == 0) {
                    continue;
                }
                std::unordered_map<int, CollisionShape>::iterator it = collision_shape->find(id);
                if (it == collision_shape->end()) {
                    continue;
                }
                CollisionShape shape = it->second;

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

std::string LevelParser::getType(XMLElement* const element) const
{
    if (element->Attribute("class")) {
        return element->Attribute("class");
    }

    if (element->Attribute("type")) {
        return element->Attribute("type");
    }

    return "";
}


std::string LevelParser::getStringAttribute(
    XMLElement* element,
    const char* attribute_name,
    std::string default_value) const
{
    if (element->Attribute(attribute_name)) {
        return element->Attribute(attribute_name);
    }
    return default_value;
}

int LevelParser::getIntAttribute(XMLElement* element, const char* attribute_name, int default_value)
    const
{
    if (element->Attribute(attribute_name)) {
        return std::stoi(element->Attribute(attribute_name));
    }
    return default_value;
}
