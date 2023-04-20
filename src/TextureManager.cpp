#include "TextureManager.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "SDL.hpp"

TextureManager& TextureManager::Instance()
{
    static TextureManager instance{};
    return instance;
}

bool TextureManager::load(const std::string& path, const std::string& id)
{
    if (textures_.find(id) != textures_.end()) {
        return false;
    }

    SDL_Texture* const texture = Game::Instance().getWindow()->loadImage(path.c_str());
    if (texture == nullptr) {
        Log::error("Fail to create Texture for: " + path);
        return false;
    }

    textures_[id] = texture;

    return true;
}

void TextureManager::draw(
    const std::string& id,
    const b2Vec2& position,
    const int width,
    const int height,
    const bool is_flipped)
{
    SDL_Rect const srcRect{0, 0, width, height};
    SDL_Rect const destRect{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        width,
        height};

    Game::Instance().getWindow()->renderImage(
        textures_[id],
        &srcRect,
        &destRect,
        0,
        0,
        is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawFrame(
    const std::string& id,
    const b2Vec2& position,
    const int width,
    const int height,
    const int row,
    const int frame,
    const float angle,
    const bool is_flipped,
    const int zoom)
{
    SDL_Rect const srcRect{width * frame, height * row, width, height};
    SDL_Rect const destRect{
        static_cast<int>(position.x * zoom),
        static_cast<int>(position.y * zoom),
        width * zoom,
        height * zoom};

    Game::Instance().getWindow()->renderImage(
        textures_[id],
        &srcRect,
        &destRect,
        angle,
        0,
        is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawTile(
    const std::string& id,
    const int margin,
    const int spacing,
    const b2Vec2& position,
    const int width,
    const int height,
    const int row,
    const int frame,
    const int zoom)
{
    SDL_Rect const srcRect{
        margin + (spacing + width) * frame,
        margin + (spacing + height) * row,
        width,
        height};

    SDL_Rect const destRect{
        static_cast<int>(position.x * zoom),
        static_cast<int>(position.y * zoom),
        static_cast<int>(width * zoom),
        static_cast<int>(height * zoom)};

    Game::Instance().getWindow()->renderImage(textures_[id], &srcRect, &destRect);
}

void TextureManager::clean()
{
    for (auto& texture : textures_) {
        Game::Instance().getWindow()->freeImage(texture.second);
    }
    textures_.clear();
}
