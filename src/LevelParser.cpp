#include "LevelParser.hpp"
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

using namespace tinyxml2;

std::unique_ptr<Level> LevelParser::parseLevel(const char* levelFile)
{
    XMLDocument levelDocument;
    if (levelDocument.LoadFile(levelFile) != XML_SUCCESS) {
        throw std::runtime_error("LevelParser: " + std::string("fail to load: ") + levelFile);
    }

    XMLElement* const pRoot = levelDocument.RootElement();
    if (pRoot == nullptr) {
        Log::error(std::string(levelFile) + ": missing  root element");
    }

    tile_size_ = std::stoi(pRoot->Attribute("tilewidth"));
    width_ = std::stoi(pRoot->Attribute("width"));
    height_ = std::stoi(pRoot->Attribute("height"));

    auto pLevel = std::make_unique<Level>();
    pLevel->setMapWidth(width_ * tile_size_);
    pLevel->setMapHeight(width_ * tile_size_);

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel.get());
        }

        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            bool isTileLayer =
                e->FirstChildElement()->Value() == std::string("data") ||
                (e->FirstChildElement()->NextSiblingElement() != 0 &&
                 e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"));
            bool isObjectLayer = e->FirstChildElement()->Value() == std::string("object");

            if (isObjectLayer) {
                parseObjectLayer(e, pLevel.get());
            } else if (isTileLayer) {
                parseTileLayer(e, pLevel.get());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(XMLElement* const pTilesetRoot, Level* pLevel)
{
    XMLElement* const pImagieEl = pTilesetRoot->FirstChildElement();

    Tileset tileset;

    if (pImagieEl->Attribute("width")) {
        tileset.width = std::stoi(pImagieEl->Attribute("width"));
    }
    if (pImagieEl->Attribute("height")) {
        tileset.height = std::stoi(pImagieEl->Attribute("height"));
    }
    if (pTilesetRoot->Attribute("firstgid")) {
        tileset.first_grid_id = std::stoi(pTilesetRoot->Attribute("firstgid"));
    }
    if (pTilesetRoot->Attribute("tilewidth")) {
        tileset.tile_width = std::stoi(pTilesetRoot->Attribute("tilewidth"));
    }
    if (pTilesetRoot->Attribute("tileheight")) {
        tileset.tile_height = std::stoi(pTilesetRoot->Attribute("tileheight"));
    }
    if (pTilesetRoot->Attribute("spacing")) {
        tileset.spacing = std::stoi(pTilesetRoot->Attribute("spacing"));
    } else {
        tileset.spacing = 0;
    }
    if (pTilesetRoot->Attribute("margin")) {
        tileset.margin = std::stoi(pTilesetRoot->Attribute("margin"));
    } else {
        tileset.margin = 0;
    }
    if (pTilesetRoot->Attribute("name")) {
        tileset.name = pTilesetRoot->Attribute("name");
    }

    tileset.columns = tileset.width / (tileset.tile_width + tileset.spacing);

    TextureManager::Instance().load(LEVEL_DIRECTORY + pImagieEl->Attribute("source"), tileset.name);
    pLevel->addTileSet(tileset);
    parseCollisionObject(pTilesetRoot, pLevel, tileset.first_grid_id);
}

void LevelParser::parseCollisionObject(XMLElement* pTilesetRoot, Level* pLevel, int firstGridID)
{
    for (XMLElement* e = pTilesetRoot->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tile")) {
            XMLElement* const obj = e->FirstChildElement()->FirstChildElement();
            int id = std::stoi(e->Attribute("id")) + firstGridID;
            bool isOneWay = getType(e) == std::string("oneway");

            int width = std::stoi(obj->Attribute("width"));
            int height = std::stoi(obj->Attribute("height"));
            pLevel->addCollisionShape(id, {isOneWay, width, height});
        }
    }
}

std::unique_ptr<GameObject> LevelParser::parseObject(
    XMLElement* const pObjectElement,
    Level* const pLevel)
{
    int x = std::stoi(pObjectElement->Attribute("x"));
    int y = std::stoi(pObjectElement->Attribute("y"));
    int width = std::stoi(pObjectElement->Attribute("width"));
    int height = std::stoi(pObjectElement->Attribute("height"));
    std::string type = getType(pObjectElement);

    std::unique_ptr<GameObject> pGameObject = GameObjectFactory::Instance().create(type);
    if (pGameObject == nullptr) {
        return nullptr;
    }

    for (XMLElement* e = pObjectElement->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement* property = e->FirstChildElement(); property != nullptr;
                 property = property->NextSiblingElement()) {
                if (property->Value() == std::string("property")) {
                    std::string propertyName = property->Attribute("name");
                    std::string propertyValue = property->Attribute("value");
                }
            }
        }
    }

    pGameObject->load(std::make_unique<LoaderParams>(LoaderParams(x, y, width, height)));

    if (type == "Player") {
        pLevel->setPlayer(dynamic_cast<Player*>(pGameObject.get()));
    }

    return pGameObject;
}

void LevelParser::parseObjectLayer(XMLElement* const pObjectEl, Level* const pLevel)
{
    auto pObjectLayer = std::make_unique<ObjectLayer>();

    bool isHaveObjects = false;
    for (XMLElement* e = pObjectEl->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {
            std::unique_ptr<GameObject> obj = parseObject(e, pLevel);
            if (obj != nullptr) {
                isHaveObjects = true;
                pObjectLayer->addGameObject(std::move(obj));
            }
        }
    }

    if (isHaveObjects) {
        pLevel->addLayer(std::move(pObjectLayer));
    }
}

std::vector<std::vector<int>> LevelParser::parseData(const std::string& dataText)
{
    std::vector<std::vector<int>> data;

    std::vector<int> layerRow(width_);
    for (int i = 0; i < height_; ++i) {
        data.push_back(layerRow);
    }

    int start = 0;
    for (int row = 0; row < height_; row++) {
        for (int col = 0; col < width_; col++) {
            int end = dataText.find(',', start);
            data[row][col] = std::stoi(dataText.substr(start, end - start));
            start = end + 1;
        }
    }

    return data;
}

void LevelParser::parseTileLayer(XMLElement* const pTileElement, Level* pLevel)
{
    auto pTileLayer =
        std::make_unique<TileLayer>(tile_size_, width_, height_, *pLevel->getTilesets());

    std::vector<std::vector<int>> IDs;
    for (XMLElement* e = pTileElement->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            IDs = parseData(e->GetText());
        }
    }

    pTileLayer->setTileIDs(IDs);
    pLevel->addLayer(std::move(pTileLayer));

    std::unordered_map<int, CollisionShape>* pCollisionShape = pLevel->getCollisionShapes();
    if (!pCollisionShape->empty()) {
        for (int row = 0; row < height_; row++) {
            for (int col = 0; col < width_; col++) {
                int id = IDs[row][col];
                if (id == 0) {
                    continue;
                }
                std::unordered_map<int, CollisionShape>::iterator it = pCollisionShape->find(id);
                if (it == pCollisionShape->end()) {
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

std::string LevelParser::getType(XMLElement* const el)
{
    if (el->Attribute("class")) {
        return el->Attribute("class");
    }

    if (el->Attribute("type")) {
        return el->Attribute("type");
    }

    return "";
}
