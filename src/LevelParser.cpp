#include "LevelParser.h"

#include <iostream>
#include <vector>
#include "Game.h"
#include "GameObjectFactory.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "TextureManager.h"
#include "TileLayer.h"

using namespace tinyxml2;

Level* LevelParser::parseLevel(const char* levelFile)
{
    XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level* pLevel = new Level();
    XMLElement* pRoot = levelDocument.RootElement();

    m_tileSize = atoi(pRoot->Attribute("tilewidth"));
    m_width = atoi(pRoot->Attribute("width"));

    Game::Instance()->setLevelWidth(m_width * m_tileSize);
    Game::Instance()->setLevelHeight(m_height * m_tileSize);

    m_height = atoi(pRoot->Attribute("height"));

    for (XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement* pProperty = e->FirstChildElement(); pProperty != NULL;
                 pProperty = pProperty->NextSiblingElement()) {
                if (pProperty->Value() == std::string("property")) {
                    parseTextures(pProperty);
                }
            }
        }
    }

    for (XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for (XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            if (e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            } else if (
                e->FirstChildElement()->Value() == std::string("data") ||
                (e->FirstChildElement()->NextSiblingElement() != 0 &&
                 e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))) {
                parseTileLayer(
                    e,
                    pLevel->getLayers(),
                    pLevel->getTilesets(),
                    pLevel->getCollisionLayers());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTextures(XMLElement* pTextureRoot)
{
    TextureManager::Instance()->load(
        pTextureRoot->Attribute("value"),
        pTextureRoot->Attribute("name"),
        Game::Instance()->getRenderer());
}

void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    std::string assetsTag = "assets/";

    XMLElement* pImagieEl = pTilesetRoot->FirstChildElement();

    Tileset tileset;

    if (pTilesetRoot->Attribute("firstgid")) {
        tileset.firstGridID = atoi(pTilesetRoot->Attribute("firstgid"));
    }
    if (pImagieEl->Attribute("width")) {
        tileset.width = atoi(pImagieEl->Attribute("width"));
    }
    if (pImagieEl->Attribute("height")) {
        tileset.height = atoi(pImagieEl->Attribute("height"));
    }
    if (pTilesetRoot->Attribute("tilewidth")) {
        tileset.tileWidth = atoi(pTilesetRoot->Attribute("tilewidth"));
    }
    if (pTilesetRoot->Attribute("tileheight")) {
        tileset.tileHeight = atoi(pTilesetRoot->Attribute("tileheight"));
    }
    if (pTilesetRoot->Attribute("spacing")) {
        tileset.spacing = atoi(pTilesetRoot->Attribute("spacing"));
    } else {
        tileset.spacing = 0;
    }

    if (pTilesetRoot->Attribute("margin")) {
        tileset.margin = atoi(pTilesetRoot->Attribute("margin"));
    } else {
        tileset.margin = 0;
    }

    if (pTilesetRoot->Attribute("name")) {
        tileset.name = pTilesetRoot->Attribute("name");
    }

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    TextureManager::Instance()->load(
        std::string("assets/") + pImagieEl->Attribute("source"),
        tileset.name,
        Game::Instance()->getRenderer());

    pTilesets->push_back(tileset);
}

GameObject* parseObject(XMLElement* pObjectElement, Level* pLevel)
{
    int x, y, width, height, numFrames, lives, callbackID, animSpeed;
    int textureWidth;
    int textureHeight;
    std::string textureID;
    std::string type;

    x = atoi(pObjectElement->Attribute("x"));
    y = atoi(pObjectElement->Attribute("y"));

    width = atoi(pObjectElement->Attribute("width"));
    height = atoi(pObjectElement->Attribute("height"));

    type = pObjectElement->Attribute("class");

    GameObject* pGameObject = GameObjectFactory::Instance()->create(type);

    for (XMLElement* e = pObjectElement->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement* property = e->FirstChildElement(); property != NULL;
                 property = property->NextSiblingElement()) {
                if (property->Value() == std::string("property")) {
                    std::string propertyName = property->Attribute("name");
                    std::string propertyValue = property->Attribute("value");

                    if (propertyName == "textureWidth") {
                        textureWidth = stoi(propertyValue);
                    } else if (propertyName == "textureHeight") {
                        textureHeight = stoi(propertyValue);
                    } else if (propertyName == "lives") {
                        lives = stoi(propertyValue);
                    } else if (propertyName == "numFrames") {
                        numFrames = stoi(propertyValue);
                    } else if (propertyName == "callbackID") {
                        callbackID = stoi(propertyValue);
                    } else if (propertyName == "textureID") {
                        textureID = propertyValue;
                    } else if (propertyName == "animSpeed") {
                        animSpeed = stoi(propertyValue);
                    }
                }
            }
        }
    }

    pGameObject->load(new LoaderParams(
        x,
        y,
        width,
        height,
        textureWidth,
        textureHeight,
        textureID,
        numFrames,
        lives,
        callbackID,
        animSpeed));
    pGameObject->setCollisionLayers(pLevel->getCollisionLayers());

    if (type == "Player") {
        Game::Instance()->setPlayer(dynamic_cast<Player*>(pGameObject));
    }

    return pGameObject;
}

void LevelParser::parseObjectLayer(
    XMLElement* pObjectEl,
    std::vector<Layer*>* pLayers,
    Level* pLevel)
{
    ObjectLayer* pObjectLayer = new ObjectLayer();

    for (XMLElement* e = pObjectEl->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("object")) {
            pObjectLayer->getGameObjects()->push_back(parseObject(e, pLevel));
        }
    }

    pLayers->push_back(pObjectLayer);
}

void LevelParser::parseTileLayer(
    tinyxml2::XMLElement* pTileElement,
    std::vector<Layer*>* pLayers,
    const std::vector<Tileset>* pTilesets,
    std::vector<TileLayer*>* pCollisionLayers)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);

    bool collidable = false;

    std::vector<std::vector<int>> data;

    std::vector<int> layerRow(m_width);
    for (int i = 0; i < m_height; i++) {
        data.push_back(layerRow);
    }

    XMLElement* pDataNode = nullptr;

    for (XMLElement* e = pTileElement->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement* property = e->FirstChildElement(); property != NULL;
                 property = property->NextSiblingElement()) {
                if (property->Value() == std::string("property")) {
                    if (property->Attribute("name") == std::string("collidable")) {
                        collidable = true;
                    }
                }
            }
        }

        if (e->Value() == std::string("data")) {
            pDataNode = e;
        }
    }

    std::string dataText = pDataNode->GetText();

    int start = 0;

    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            int end = dataText.find(',', start);
            data[row][col] = stoi(dataText.substr(start, end - start));
            start = end + 1;
        }
    }

    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);
    if (collidable) {
        pCollisionLayers->push_back(pTileLayer);
    }
    pLayers->push_back(pTileLayer);
}
