#pragma once

#include <vector>
#include "Layer.hpp"
#include "Level.hpp"

class TileLayer final : public Layer
{
public:
    TileLayer(
        int const tileSize,
        int const mapWidth,
        int const mapHeight,
        const std::vector<Tileset>& tilesets);
    void update();
    void render() const;

    void setTileIDs(const std::vector<std::vector<int>>& data);
    void setTileSize(int const tileSize);
    void setPosition(const b2Vec2& position);

    const std::vector<std::vector<int>>& getTileIDs();
    int getTileSize() const;
    Tileset getTilesetByID(int const tileID) const;
    b2Vec2 getPosition() const;


private:
    int m_tileSize;
    int m_nCols;
    int m_nRows;
    b2Vec2 m_position;
    const std::vector<Tileset>& m_tilesets;
    std::vector<std::vector<int>> m_tileIDs;
};
