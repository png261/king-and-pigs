#include "TileLayer.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

TileLayer::TileLayer(
    int const tileSize,
    int const mapWidth,
    int const mapHeight,
    const std::vector<Tileset>& tilesets)
    : m_tileSize(tileSize)
    , m_tilesets(tilesets)
    , m_position(0, 0)
{
    m_numColumns = mapWidth;
    m_numRows = mapHeight;

    m_mapWidth = mapWidth;
}

void TileLayer::update(Level* const pLevel) {}

void TileLayer::render()
{
    int x, y, x2, y2 = 0;

    x = m_position.x / m_tileSize;
    y = m_position.y / m_tileSize;

    x2 = int(m_position.x) % m_tileSize;
    y2 = int(m_position.y) % m_tileSize;

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x];

            const int EMPTY_TILE = 0;

            if (id == EMPTY_TILE) {
                continue;
            }

            b2Vec2 position = b2Vec2(((j * m_tileSize) - x2), ((i * m_tileSize) - y2)) -
                              Camera::Instance()->getPosition();

            bool isInViewPort = position.x > -m_tileSize &&
                                position.x < Game::Instance()->getWindow()->getWidth() &&
                                position.y > -m_tileSize &&
                                position.y < Game::Instance()->getWindow()->getHeight();

            if (isInViewPort == false) {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            TextureManager::Instance()->drawTile(
                tileset.name,
                tileset.margin,
                tileset.spacing,
                position,
                m_tileSize,
                m_tileSize,
                (id - tileset.firstGridID) / tileset.numColumns,
                (id - tileset.firstGridID) % tileset.numColumns);
        }
    }
}

Tileset TileLayer::getTilesetByID(int const tileID) const
{
    for (int i = 0; i < m_tilesets.size(); i++) {
        if (i + 1 <= m_tilesets.size() - 1) {
            if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        } else {
            return m_tilesets[i];
        }
    }

    Log::warning("did not find tileset, return empty tileset");
    return Tileset{};
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
    m_tileIDs = data;
}

void TileLayer::setTileSize(int const tileSize)
{
    m_tileSize = tileSize;
}

int TileLayer::getTileSize() const
{
    return m_tileSize;
}

const std::vector<std::vector<int>>& TileLayer::getTileIDs()
{
    return m_tileIDs;
}

b2Vec2 TileLayer::getPosition() const
{
    return m_position;
}

void TileLayer::setPosition(b2Vec2 const position)
{
    m_position = position;
}
