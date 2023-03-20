#include "Level.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

Level::Level()
{
    m_eventLayer = new ObjectLayer();
}

Level::~Level()
{
    for (auto& layer : m_layers) {
        delete layer;
    }
    m_layers.clear();
    Log::log("deleted level");
}

void Level::render()
{
    for (auto& layer : m_layers) {
        layer->render();
    }
    m_eventLayer->render();
}

void Level::update()
{
    for (auto& layer : m_layers) {
        layer->update();
    }
    m_eventLayer->update();
}

std::vector<Tileset>* Level::getTilesets()
{
    return &m_tilesets;
}

std::map<int, CollisionShape>* Level::getCollisionShapes()
{
    return &m_collisionShapes;
}

std::vector<Layer*>* Level::getLayers()
{
    return &m_layers;
}

void Level::addLayer(Layer* layer)
{
    m_layers.push_back(layer);
}

void Level::addTileSet(Tileset tileset)
{
    m_tilesets.push_back(tileset);
}

void Level::addCollisionShape(std::pair<int, CollisionShape> shape)
{
    m_collisionShapes.insert(shape);
}

Player* Level::getPlayer()
{
    return m_pPlayer;
}

void Level::setPlayer(Player* player)
{
    m_pPlayer = player;
}

void Level::spawnGameObject(std::string type, std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject* const pGameObject = GameObjectFactory::Instance()->create(type);
    pGameObject->load(std::move(pParams));
    m_eventLayer->addGameObject(pGameObject);
}
