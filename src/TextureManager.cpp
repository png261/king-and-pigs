#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include "Log.hpp"

TextureManager* TextureManager::Instance()
{
    static TextureManager* s_pInstance = new TextureManager;
    return s_pInstance;
}

bool TextureManager::load(
    std::string filename,
    std::string textureID,
    SDL_Renderer* pRenderer,
    int nFrames)
{
    if (m_textureMap.find(textureID) != m_textureMap.end()) {
        Log::warning("textureID already exists");
        return false;
    }

    SDL_Texture* pTexture = IMG_LoadTexture(pRenderer, filename.c_str());
    if (pTexture == NULL) {
        Log::error("fail to create Texture for: " + filename);
        return false;
    }

    m_textureMap[textureID] = pTexture;
    m_nFrameMap[textureID] = nFrames;

    return true;
}

void TextureManager::draw(
    std::string textureID,
    int x,
    int y,
    int width,
    int height,
    SDL_Renderer* pRenderer,
    SDL_RendererFlip flip)
{
    SDL_Rect srcRect{0, 0, width, height};
    SDL_Rect destRect{x, y, width, height};

    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(pRenderer, &destRect);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

    SDL_RenderCopyEx(pRenderer, m_textureMap[textureID], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(
    std::string id,
    int x,
    int y,
    int width,
    int height,
    int currentRow,
    int currentFrame,
    SDL_Renderer* pRenderer,
    double angle,
    int alpha,
    SDL_RendererFlip flip)
{
    SDL_Rect srcRect{width * currentFrame, height * currentRow, width, height};
    SDL_Rect destRect{x, y, width, height};

    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(pRenderer, &destRect);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(
    std::string id,
    int margin,
    int spacing,
    int x,
    int y,
    int width,
    int height,
    int currentRow,
    int currentFrame,
    SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect{
        margin + (spacing + width) * currentFrame,
        margin + (spacing + height) * currentRow,
        width,
        height};
    SDL_Rect destRect{x, y, width, height};

    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(pRenderer, &destRect);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
