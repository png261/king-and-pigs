#include "TextureManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "SDL.hpp"

std::shared_ptr<TextureManager> TextureManager::Instance()
{
    static std::shared_ptr<TextureManager> s_pInstance{new TextureManager};
    return s_pInstance;
}

bool TextureManager::load(const std::string path, const std::string id)
{
    if (m_textureMap.find(id) != m_textureMap.end()) {
        return false;
    }

    SDL_Texture* const pTexture = Game::Instance()->getWindow()->loadImage(path.c_str());
    if (pTexture == nullptr) {
        Log::error("Fail to create Texture for: " + path);
        return false;
    }

    m_textureMap[id] = pTexture;

    return true;
}

void TextureManager::draw(
    const std::string id,
    const b2Vec2 position,
    const int width,
    const int height,
    const bool bFlipped)
{
    SDL_Rect const srcRect{0, 0, width, height};
    SDL_Rect const destRect{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        width,
        height};

    Game::Instance()->getWindow()->renderImage(
        m_textureMap[id],
        &srcRect,
        &destRect,
        0,
        0,
        bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawFrame(
    const std::string id,
    const b2Vec2 position,
    const int width,
    const int height,
    const int currentRow,
    const int currentFrame,
    const float angle,
    const bool bFlipped,
    const int zoom)
{
    SDL_Rect const srcRect{width * currentFrame, height * currentRow, width, height};
    SDL_Rect const destRect{
        static_cast<int>(position.x * zoom),
        static_cast<int>(position.y * zoom),
        width * zoom,
        height * zoom};

    Game::Instance()->getWindow()->renderImage(
        m_textureMap[id],
        &srcRect,
        &destRect,
        angle,
        0,
        bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawTile(
    const std::string id,
    const int margin,
    const int spacing,
    const b2Vec2 position,
    const int width,
    const int height,
    const int currentRow,
    const int currentFrame,
    const int zoom)
{
    SDL_Rect const srcRect{
        margin + (spacing + width) * currentFrame,
        margin + (spacing + height) * currentRow,
        width,
        height};

    SDL_Rect const destRect{
        static_cast<int>(position.x * zoom),
        static_cast<int>(position.y * zoom),
        static_cast<int>(width * zoom),
        static_cast<int>(height * zoom)};

    Game::Instance()->getWindow()->renderImage(m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::clean()
{
    m_textureMap.clear();
}
