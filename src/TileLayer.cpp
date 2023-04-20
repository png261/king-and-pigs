#include "TileLayer.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

TileLayer::TileLayer(
    int const tile_size,
    int const columns,
    int const rows,
    const std::vector<Tileset>& tile_sets)
    : tile_size_(tile_size)
    , columns_(columns)
    , rows_(rows)
    , position_(0, 0)
    , tile_sets_(tile_sets)
{}

void TileLayer::update() {}

void TileLayer::render() const
{
    int x, y, x2, y2 = 0;

    x = position_.x / tile_size_;
    y = position_.y / tile_size_;

    x2 = int(position_.x) % tile_size_;
    y2 = int(position_.y) % tile_size_;

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < columns_; j++) {
            int id = tile_ids_[i + y][j + x];

            const int EMPTY_TILE = 0;

            if (id == EMPTY_TILE) {
                continue;
            }

            b2Vec2 position = b2Vec2(((j * tile_size_) - x2), ((i * tile_size_) - y2)) -
                              Camera::Instance().getPosition();

            bool isInViewPort =
                position.x > -tile_size_ && position.x < Game::Instance().getWindow()->getWidth() &&
                position.y > -tile_size_ && position.y < Game::Instance().getWindow()->getHeight();

            if (!isInViewPort) {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            TextureManager::Instance().drawTile(
                tileset.name,
                tileset.margin,
                tileset.spacing,
                position,
                tile_size_,
                tile_size_,
                (id - tileset.first_grid_id) / tileset.columns,
                (id - tileset.first_grid_id) % tileset.columns,
                Camera::Instance().getZoom());
        }
    }
}

Tileset TileLayer::getTilesetByID(int const tile_id) const
{
    for (std::size_t i = 0; i < tile_sets_.size(); ++i) {
        if (i + 1 <= tile_sets_.size() - 1) {
            if (tile_id >= tile_sets_[i].first_grid_id &&
                tile_id < tile_sets_[i + 1].first_grid_id) {
                return tile_sets_[i];
            }
        } else {
            return tile_sets_[i];
        }
    }

    Log::warning("can't find tileset, return empty tileset");
    return {};
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
    tile_ids_ = data;
}

void TileLayer::setTileSize(int const tile_size)
{
    tile_size_ = tile_size;
}

int TileLayer::getTileSize() const
{
    return tile_size_;
}

const std::vector<std::vector<int>>& TileLayer::getTileIDs()
{
    return tile_ids_;
}

b2Vec2 TileLayer::getPosition() const
{
    return position_;
}

void TileLayer::setPosition(const b2Vec2& position)
{
    position_ = position;
}
