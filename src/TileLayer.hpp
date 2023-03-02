#ifndef TILE_LAYER_HPP
#define TILE_LAYER_HPP

#include <vector>
#include "Layer.hpp"
#include "Level.hpp"

class TileLayer : public Layer
{
public:
    TileLayer(
        int const tileSize,
        int const mapWidth,
        int const mapHeight,
        const std::vector<Tileset>& tilesets);
    ~TileLayer() {}
    virtual void update(Level* const pLevel);
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int>>& data);
    void setTileSize(int const tileSize);
    void setMapWidth(int const mapWidth);
    void setPosition(b2Vec2 const position);

    const std::vector<std::vector<int>>& getTileIDs();
    int getMapWidth() const;
    int getTileSize() const;
    Tileset getTilesetByID(int const tileID) const;
    b2Vec2 getPosition() const;


private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    int m_mapWidth;

    b2Vec2 m_position;

    const std::vector<Tileset>& m_tilesets;

    std::vector<std::vector<int>> m_tileIDs;
};

#endif
