#include "LevelParser.hpp"

#include <iostream>
#include <vector>
#include "Box2D.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "Layer.hpp"
#include "Level.hpp"
#include "Log.hpp"
#include "ObjectLayer.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

using namespace tinyxml2;

Level* LevelParser::parseLevel(const char* levelFile)
{
    XMLDocument levelDocument;
    if (levelDocument.LoadFile(levelFile) != XML_SUCCESS) {
        Log::error(std::string("fail to load level file: ") + levelFile);
    }

    Level* const pLevel = new Level();
    XMLElement* const pRoot = levelDocument.RootElement();
    if (pRoot == nullptr) {
        Log::error(std::string(levelFile) + ": missing  root element");
    }

    m_tileSize = std::stoi(pRoot->Attribute("tilewidth"));
    m_width = std::stoi(pRoot->Attribute("width"));
    m_height = std::stoi(pRoot->Attribute("height"));

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement* pProperty = e->FirstChildElement(); pProperty != nullptr;
                 pProperty = pProperty->NextSiblingElement()) {
                if (pProperty->Value() == std::string("property")) {
                    parseTextures(pProperty);
                }
            }
        }
    }

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel->getTilesets(), pLevel->getCollisionShapes());
        }
    }

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            bool isTileLayer =
                e->FirstChildElement()->Value() == std::string("data") ||
                (e->FirstChildElement()->NextSiblingElement() != 0 &&
                 e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"));
            bool isObjectLayer = e->FirstChildElement()->Value() == std::string("object");

            if (isObjectLayer) {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            } else if (isTileLayer) {
                parseTileLayer(
                    e,
                    pLevel->getLayers(),
                    pLevel->getTilesets(),
                    pLevel->getCollisionShapes());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTextures(XMLElement* const pTextureRoot)
{
    TextureManager::Instance()->load(
        pTextureRoot->Attribute("value"),
        pTextureRoot->Attribute("name"));
}

void LevelParser::parseTilesets(
    XMLElement* const pTilesetRoot,
    std::vector<Tileset>* const pTilesets,
    std::map<int, CollisionShape>* const pCollisionShapes)
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
        tileset.firstGridID = std::stoi(pTilesetRoot->Attribute("firstgid"));
    }
    if (pTilesetRoot->Attribute("tilewidth")) {
        tileset.tileWidth = std::stoi(pTilesetRoot->Attribute("tilewidth"));
    }
    if (pTilesetRoot->Attribute("tileheight")) {
        tileset.tileHeight = std::stoi(pTilesetRoot->Attribute("tileheight"));
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

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    TextureManager::Instance()->load(ASSETS_DIR + pImagieEl->Attribute("source"), tileset.name);
    pTilesets->push_back(tileset);
    parseCollisionObject(pTilesetRoot, tileset.firstGridID, pCollisionShapes);
}

void LevelParser::parseCollisionObject(
    XMLElement* pTilesetRoot,
    int firstGridID,
    std::map<int, CollisionShape>* pCollisionShapes)
{
    for (XMLElement* e = pTilesetRoot->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tile")) {
            XMLElement* obj = e->FirstChildElement()->FirstChildElement();
            int id = std::stoi(e->Attribute("id")) + firstGridID;
            int width = std::stoi(obj->Attribute("width"));
            int height = std::stoi(obj->Attribute("height"));
            pCollisionShapes->insert(std::pair<int, CollisionShape>(id, {width, height}));
        }
    }
}

GameObject* parseObject(XMLElement* const pObjectElement, Level* const pLevel)
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    std::string type = "";

    x = std::stoi(pObjectElement->Attribute("x"));
    y = std::stoi(pObjectElement->Attribute("y"));

    width = std::stoi(pObjectElement->Attribute("width"));
    height = std::stoi(pObjectElement->Attribute("height"));

    type = pObjectElement->Attribute("class");

    GameObject* const pGameObject = GameObjectFactory::Instance()->create(type);

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

    pGameObject->load(new LoaderParams(x, y, width, height));

    if (type == "Player") {
        pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
    }

    return pGameObject;
}

void LevelParser::parseObjectLayer(
    XMLElement* const pObjectEl,
    std::vector<Layer*>* const pLayers,
    Level* const pLevel)
{
    ObjectLayer* const pObjectLayer = new ObjectLayer();

    for (XMLElement* e = pObjectEl->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {
            pObjectLayer->getGameObjects()->push_back(parseObject(e, pLevel));
        }
    }

    if (!pObjectLayer->getGameObjects()->empty()) {
        pLayers->push_back(pObjectLayer);
    }
}

std::vector<std::vector<int>> LevelParser::parseData(std::string dataText)
{
    std::vector<std::vector<int>> data;

    std::vector<int> layerRow(m_width);
    for (int i = 0; i < m_height; i++) {
        data.push_back(layerRow);
    }

    int start = 0;
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            int end = dataText.find(',', start);
            data[row][col] = std::stoi(dataText.substr(start, end - start));
            start = end + 1;
        }
    }

    return data;
}

void LevelParser::parseTileLayer(
    XMLElement* const pTileElement,
    std::vector<Layer*>* const pLayers,
    std::vector<Tileset>* const pTilesets,
    std::map<int, CollisionShape>* const pCollisionShape)
{
    TileLayer* const pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);

    std::vector<std::vector<int>> IDs;
    for (XMLElement* e = pTileElement->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            IDs = parseData(e->GetText());
        }
    }

    pTileLayer->setTileIDs(IDs);
    pLayers->push_back(pTileLayer);

    if (!pCollisionShape->empty()) {
        for (int row = 0; row < m_height; row++) {
            for (int col = 0; col < m_width; col++) {
                int id = IDs[row][col];
                if (id == 0) {
                    continue;
                }
                std::map<int, CollisionShape>::iterator shape = pCollisionShape->find(id);
                if (shape == pCollisionShape->end()) {
                    continue;
                }

                b2Vec2 position = m_tileSize * b2Vec2(col, row);
                if (id == 59) {
                    std::cout << position.x << " " << position.y << std::endl;
                }

                Box2D::Instance()->createCollisionObject(
                    shape->second.width,
                    shape->second.height,
                    position);
            }
        }
    }
}
