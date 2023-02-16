#ifndef TILE_LAYER_HPP
#define TILE_LAYER_HPP

#include <vector>
#include "Layer.hpp"
#include "Level.hpp"
#include "Vector2D.hpp"

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets);
    ~TileLayer() {}
    virtual void update(Level* pLevel);
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int>>& data);
    void setTileSize(int tileSize);
    void setMapWidth(int mapWidth);
    int getMapWidth();
    int getTileSize();
    Tileset getTilesetByID(int tileID);

    const std::vector<std::vector<int>>& getTileIDs();
    const Vector2D getPosition();
    void setPosition(Vector2D position);

private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    int m_mapWidth;

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    float diff;

    const std::vector<Tileset>& m_tilesets;

    std::vector<std::vector<int>> m_tileIDs;
};

#endif
