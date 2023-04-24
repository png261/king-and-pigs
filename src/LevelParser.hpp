#pragma once

#include <json/json.h>

#include "Level.hpp"

class LevelParser final
{
public:
    std::unique_ptr<Level> parseLevel(const std::string& path);

private:
    void parseTileset(const Json::Value& tileset_data, Level* const level) const;
    void parseObjectLayer(const Json::Value& layer, Level* const level) const;
    void parseTileLayer(const Json::Value& layer, Level* const level) const;
    std::unique_ptr<GameObject> parseObject(const Json::Value& object_data, Level* const level)
        const;

    int tile_size_;
    int width_;
    int height_;
};
