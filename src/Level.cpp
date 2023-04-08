#include "Level.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

Level::Level()
{
    m_spawnLayer = std::make_unique<ObjectLayer>();
}

Level::~Level() {}

void Level::render()
{
    for (const auto& layer : m_layers) {
        layer->render();
    }
    m_spawnLayer->render();
}

void Level::update()
{
    for (const auto& layer : m_layers) {
        layer->update();
    }
    m_spawnLayer->update();
}

std::vector<Tileset>* Level::getTilesets()
{
    return &m_tilesets;
}

std::unordered_map<int, CollisionShape>* Level::getCollisionShapes()
{
    return &m_collisionShapes;
}

void Level::addLayer(Layer* const layer)
{
    m_layers.push_back(std::unique_ptr<Layer>(layer));
}

void Level::addTileSet(const Tileset tileset)
{
    m_tilesets.push_back(tileset);
}

void Level::addCollisionShape(const int id, const CollisionShape shape)
{
    m_collisionShapes[id] = shape;
}

Player* Level::getPlayer() const
{
    return m_pPlayer;
}

void Level::setPlayer(Player* const player)
{
    m_pPlayer = player;
}

GameObject* Level::spawnGameObject(
    const std::string type,
    std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject* const pGameObject = GameObjectFactory::Instance()->create(type);
    pGameObject->load(std::move(pParams));
    m_spawnLayer->addGameObject(pGameObject);
    return pGameObject;
}
