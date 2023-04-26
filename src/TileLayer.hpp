#pragma once

#include <vector>

#include "Layer.hpp"
#include "Level.hpp"

class TileLayer final : public Layer
{
public:
    TileLayer(
        int const tile_size,
        int const map_width,
        int const map_height,
        const std::vector<Tileset>& tile_sets);

    void update();
    void render() const;

    void setTileData(const std::vector<int>& data);
    void setTileSize(int const tile_size);
    void setPosition(const b2Vec2& position);

    const std::vector<int>& getTileData() const;
    int getTileSize() const;
    Tileset getTilesetByID(int const tile_id) const;
    b2Vec2 getPosition() const;


private:
    int tile_size_;
    int columns_;
    int rows_;
    b2Vec2 position_;
    const std::vector<Tileset>& tile_sets_;
    std::vector<int> tile_ids_;
};
