#include "TextureManager.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "SDL.hpp"

TextureManager* TextureManager::Instance()
{
    static TextureManager* s_pInstance = new TextureManager;
    return s_pInstance;
}

bool TextureManager::load(std::string filename, std::string textureID)
{
    if (m_textureMap.find(textureID) != m_textureMap.end()) {
        Log::warning("textureID already exists");
        return false;
    }

    SDL_Texture* pTexture = TheGame::Instance()->getWindow()->loadImage(filename.c_str());
    if (pTexture == nullptr) {
        Log::error("fail to create Texture for: " + filename);
        return false;
    }

    m_textureMap[textureID] = pTexture;

    return true;
}

void TextureManager::draw(
    std::string textureID,
    b2Vec2 position,
    int width,
    int height,
    bool bFlipped)
{
    SDL_Rect srcRect{0, 0, width, height};
    SDL_Rect destRect{static_cast<int>(position.x), static_cast<int>(position.y), width, height};

    TheGame::Instance()->getWindow()->renderImage(
        m_textureMap[textureID],
        &srcRect,
        &destRect,
        0,
        0,
        bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawFrame(
    std::string id,
    b2Vec2 position,
    int width,
    int height,
    int currentRow,
    int currentFrame,
    float angle,
    bool bFlipped)
{
    SDL_Rect srcRect{width * currentFrame, height * currentRow, width, height};
    SDL_Rect destRect{static_cast<int>(position.x), static_cast<int>(position.y), width, height};

    TheGame::Instance()->getWindow()->renderImage(
        m_textureMap[id],
        &srcRect,
        &destRect,
        angle,
        0,
        bFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::drawTile(
    std::string id,
    int margin,
    int spacing,
    b2Vec2 position,
    int width,
    int height,
    int currentRow,
    int currentFrame)
{
    SDL_Rect srcRect{
        margin + (spacing + width) * currentFrame,
        margin + (spacing + height) * currentRow,
        width,
        height};
    SDL_Rect destRect{static_cast<int>(position.x), static_cast<int>(position.y), width, height};

    TheGame::Instance()->getWindow()->renderImage(m_textureMap[id], &srcRect, &destRect);
}
