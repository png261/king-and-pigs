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
    if (textures_.count(id) != 0) {
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
    const bool is_flip,
    const int zoom) const
{
    SDL_Rect src_rect{0, 0, 0, 0};
    SDL_QueryTexture(textures_.at(id), NULL, NULL, &src_rect.w, &src_rect.h);

    SDL_Rect const dest_rect{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        width * zoom,
        height * zoom};

    Game::Instance().getWindow()->renderImage(
        textures_.at(id),
        &src_rect,
        &dest_rect,
        0,
        0,
        is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawFrame(
    const std::string& id,
    const b2Vec2& position,
    const int width,
    const int height,
    const int row,
    const int frame,
    const float angle,
    const bool is_flip,
    const int zoom) const
{
    SDL_Rect const src_rect{width * frame, height * row, width, height};
    SDL_Rect const dest_rect{
        static_cast<int>(position.x * zoom),
        static_cast<int>(position.y * zoom),
        width * zoom,
        height * zoom};


    Game::Instance().getWindow()->renderImage(
        textures_.at(id),
        &src_rect,
        &dest_rect,
        angle,
        0,
        is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
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
    const int zoom) const
{
    SDL_Rect const src_rect{
        margin + (spacing + width) * frame,
        margin + (spacing + height) * row,
        width,
        height};

    SDL_Rect const dest_rect{
        static_cast<int>(position.x * zoom),
        static_cast<int>(position.y * zoom),
        static_cast<int>(width * zoom),
        static_cast<int>(height * zoom)};

    Game::Instance().getWindow()->renderImage(textures_.at(id), &src_rect, &dest_rect);
}

void TextureManager::clean()
{
    for (auto& texture : textures_) {
        Game::Instance().getWindow()->freeImage(texture.second);
    }
    textures_.clear();
}
