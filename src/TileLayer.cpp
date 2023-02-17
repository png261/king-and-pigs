#include "TileLayer.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

TileLayer::TileLayer(
    int tileSize,
    int mapWidth,
    int mapHeight,
    const std::vector<Tileset>& tilesets)
    : m_tileSize(tileSize)
    , m_tilesets(tilesets)
    , m_position(0, 0)
    , m_velocity(0, 0)
{
    m_numColumns = mapWidth;
    m_numRows = mapHeight;

    m_mapWidth = mapWidth;
}

void TileLayer::update(Level* pLevel) {}

void TileLayer::render()
{
    int x, y, x2, y2 = 0;

    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;

    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x];

            if (id == 0) {
                continue;
            }

            if (((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().m_x < -m_tileSize ||
                ((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().m_x >
                    TheGame::Instance()->getGameWidth()) {
                continue;
            }

            if (((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().m_y < -m_tileSize ||
                ((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().m_y >
                    TheGame::Instance()->getGameHeight()) {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            id--;

            TheTextureManager::Instance()->drawTile(
                tileset.name,
                tileset.margin,
                tileset.spacing,
                ((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().m_x,
                ((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().m_y,
                m_tileSize,
                m_tileSize,
                (id - (tileset.firstGridID - 1)) / tileset.numColumns,
                (id - (tileset.firstGridID - 1)) % tileset.numColumns);
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID)
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

    Log::warning("did not find tileset, returning empty tileset");
    Tileset t;
    return t;
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
    m_tileIDs = data;
}

void TileLayer::setTileSize(int tileSize)
{
    m_tileSize = tileSize;
}

void TileLayer::setMapWidth(int mapWidth)
{
    m_mapWidth = mapWidth;
}

int TileLayer::getMapWidth()
{
    return m_mapWidth;
}

int TileLayer::getTileSize()
{
    return m_tileSize;
}

const std::vector<std::vector<int>>& TileLayer::getTileIDs()
{
    return m_tileIDs;
}

const Vector2D TileLayer::getPosition()
{
    return m_position;
}

void TileLayer::setPosition(Vector2D position)
{
    m_position = position;
}
