#pragma once

#include <string>
#include <unordered_map>

#include "PhysicManager.hpp"
#include "SDL.hpp"

class TextureManager final
{
public:
    static TextureManager& Instance();
    TextureManager(TextureManager const&) = delete;
    TextureManager& operator=(TextureManager const&) = delete;

    bool load(const std::string& path, const std::string& id);

    void draw(
        const std::string& id,
        const b2Vec2& position,
        const int width,
        const int height,
        const bool is_flip = false,
        const int zoom = 1) const;

    void drawFrame(
        const std::string& id,
        const b2Vec2& position,
        const int width,
        const int height,
        const int row,
        const int frame,
        const float angle = 0,
        const bool is_flip = false,
        const int zoom = 1) const;

    void drawTile(
        const std::string& id,
        const int margin,
        const int spacing,
        const b2Vec2& position,
        const int width,
        const int height,
        const int row,
        const int frame,
        const int zoom = 1) const;

    void clean();

private:
    TextureManager() = default;
    std::unordered_map<std::string, SDL_Texture*> textures_;
};
