#include "TextureManager.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

bool TextureManager::load(std::string filename, std::string textureID,
                          int nFrames, SDL_Renderer *pRenderer) {
    SDL_Surface *pTempSurface = IMG_Load(filename.c_str());
    if (pTempSurface == NULL) {
        SDL_Log("fail to load %s", filename.c_str());
        return false;
    }

SDL_Texture *pTexture =
        SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    if (pTexture == NULL) {
        SDL_Log("fail to create Texture for %s", filename.c_str());
        return false;
    }

    m_textureMap[textureID] = Texture {pTexture, nFrames};

    return true;
}

void TextureManager::draw(std::string textureID, int x, int y, int w, int h,
                          SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[textureID].pTexture, &srcRect,
                     &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width,
                               int height, int currentRow, int currentFrame,
                               SDL_Renderer *pRenderer, double angle, int alpha,
                               SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = width;
    srcRect.h = height;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
    destRect.x = x;
    destRect.y = y;

    SDL_SetTextureAlphaMod(m_textureMap[id].pTexture, alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id].pTexture, &srcRect, &destRect,
                     angle, 0, flip);
}

void TextureManager::clean() { m_textureMap.clear(); }
