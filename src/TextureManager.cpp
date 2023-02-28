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

    SDL_Renderer* pRenderer = Game::Instance()->getRenderer();
    SDL_Texture* pTexture = IMG_LoadTexture(pRenderer, filename.c_str());
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
    SDL_Renderer* pRenderer = Game::Instance()->getRenderer();

    SDL_Rect srcRect{0, 0, width, height};
    SDL_Rect destRect{(int)position.x, (int)position.y, width, height};

    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(pRenderer, &destRect);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

    SDL_RenderCopyEx(
        pRenderer,
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
    SDL_Renderer* pRenderer = Game::Instance()->getRenderer();

    SDL_Rect srcRect{width * currentFrame, height * currentRow, width, height};
    SDL_Rect destRect{(int)position.x, (int)position.y, width, height};

    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(pRenderer, &destRect);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

    SDL_RenderCopyEx(
        pRenderer,
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
    SDL_Renderer* pRenderer = Game::Instance()->getRenderer();
    SDL_Rect srcRect{
        margin + (spacing + width) * currentFrame,
        margin + (spacing + height) * currentRow,
        width,
        height};
    SDL_Rect destRect{(int)position.x, (int)position.y, width, height};

    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(pRenderer, &destRect);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
