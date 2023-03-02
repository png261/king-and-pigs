#include "LevelParser.hpp"

#include <vector>
#include "Box2D.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "Layer.hpp"
#include "ObjectLayer.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

using namespace tinyxml2;

Level* LevelParser::parseLevel(const char* levelFile)
{
    XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level* const pLevel = new Level();
    XMLElement* const pRoot = levelDocument.RootElement();

    m_tileSize = atoi(pRoot->Attribute("tilewidth"));
    m_width = atoi(pRoot->Attribute("width"));

    Game::Instance()->setLevelWidth(m_width * m_tileSize);
    Game::Instance()->setLevelHeight(m_height * m_tileSize);

    m_height = atoi(pRoot->Attribute("height"));

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
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            if (e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            } else if (
                e->FirstChildElement()->Value() == std::string("data") ||
                (e->FirstChildElement()->NextSiblingElement() != 0 &&
                 e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))) {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
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
    std::vector<Tileset>* const pTilesets)
{
    const std::string assetsTag = "assets/";

    XMLElement* const pImagieEl = pTilesetRoot->FirstChildElement();

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

    TextureManager::Instance()->load(assetsTag + pImagieEl->Attribute("source"), tileset.name);

    pTilesets->push_back(tileset);
}

GameObject* parseObject(XMLElement* const pObjectElement, Level* const pLevel)
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int numFrames = 0;
    int lives = 0;
    int callbackID = 0;
    int textureWidth = 0;
    int textureHeight = 0;
    int textureX = 0;
    int textureY = 0;
    std::string type = "";

    x = atoi(pObjectElement->Attribute("x"));
    y = atoi(pObjectElement->Attribute("y"));

    width = atoi(pObjectElement->Attribute("width"));
    height = atoi(pObjectElement->Attribute("height"));

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

                    if (propertyName == "textureWidth") {
                        textureWidth = stoi(propertyValue);
                    }
                    if (propertyName == "textureY") {
                        textureY = stoi(propertyValue);
                    }
                    if (propertyName == "textureX") {
                        textureX = stoi(propertyValue);
                    } else if (propertyName == "textureHeight") {
                        textureHeight = stoi(propertyValue);
                    } else if (propertyName == "lives") {
                        lives = stoi(propertyValue);
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
        numFrames,
        lives,
        callbackID,
        textureX,
        textureY));

    if (type == "Player") {
        Game::Instance()->setPlayer(dynamic_cast<Player*>(pGameObject));
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

    pLayers->push_back(pObjectLayer);
}

void LevelParser::parseTileLayer(
    XMLElement* const pTileElement,
    std::vector<Layer*>* const pLayers,
    std::vector<Tileset>* const pTilesets)
{
    TileLayer* const pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);

    bool collidable = false;

    std::vector<std::vector<int>> data;

    std::vector<int> layerRow(m_width);
    for (int i = 0; i < m_height; i++) {
        data.push_back(layerRow);
    }

    XMLElement* pDataNode = nullptr;

    for (XMLElement* e = pTileElement->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement* property = e->FirstChildElement(); property != nullptr;
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

    std::string const dataText = pDataNode->GetText();

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
        for (int row = 0; row < m_height; row++) {
            for (int col = 0; col < m_width; col++) {
                int id = data[row][col];
                if (id == 0) {
                    continue;
                }

                Box2D::Instance()->createWall(
                    m_tileSize,
                    b2Vec2(
                        col * m_tileSize + m_tileSize / 2.0f,
                        row * m_tileSize + m_tileSize / 2.0f));
            }
        }
    }

    pLayers->push_back(pTileLayer);
}
