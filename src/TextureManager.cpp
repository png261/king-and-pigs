#include "TextureManager.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "SDL.hpp"

TextureManager* TextureManager::Instance()
{
    static TextureManager* const s_pInstance = new TextureManager;
    return s_pInstance;
}

bool TextureManager::load(const std::string filename, const std::string textureID)
{
    if (m_textureMap.find(textureID) != m_textureMap.end()) {
        Log::warning("textureID already exists");
        return false;
    }

    SDL_Texture* const pTexture = Game::Instance()->getWindow()->loadImage(filename.c_str());
    if (pTexture == nullptr) {
        Log::error("fail to create Texture for: " + filename);
        return false;
    }

    m_textureMap[textureID] = pTexture;

    return true;
}

void TextureManager::draw(
    const std::string textureID,
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
        m_textureMap[textureID],
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
    const bool bFlipped)
{
    SDL_Rect const srcRect{width * currentFrame, height * currentRow, width, height};
    SDL_Rect const destRect{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        width,
        height};

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
    const int currentFrame)
{
    SDL_Rect const srcRect{
        margin + (spacing + width) * currentFrame,
        margin + (spacing + height) * currentRow,
        width,
        height};
    SDL_Rect const destRect{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        width,
        height};

    Game::Instance()->getWindow()->renderImage(m_textureMap[id], &srcRect, &destRect);
}
