#pragma once

#include <nlohmann/json.hpp>

#include "Level.hpp"

class LevelParser final
{
public:
    std::unique_ptr<Level> parseLevel(const std::string& path);

private:
    void loadTileset(const nlohmann::json& tileset_data, Level* const level) const;
    void parseObjectLayer(const nlohmann::json& layer, Level* const level) const;
    void parseTileLayer(const nlohmann::json& layer, Level* const level) const;
    std::unique_ptr<Object> parseObject(const nlohmann::json& object_data, Level* const level)
        const;

    int tile_size_;
    int width_;
    int height_;
};
