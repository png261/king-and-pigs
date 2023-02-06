#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

struct Texture {
    SDL_Texture *pTexture;
    int nFrames;
};

class TextureManager {
  public:
    static TextureManager *Instance() {
        static TextureManager *s_pInstance = new TextureManager;
        return s_pInstance;
    }

    bool load(std::string filename, std::string textureID, int nFrames,
              SDL_Renderer *pRenderer);
    void draw(std::string textureID, int x, int y, int width, int height,
              SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer *pRenderer,
                   double angle, int alpha = 255,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getNFrames(std::string textureID) {
        if (m_textureMap.find(textureID) == m_textureMap.end()) {
            return 1;
        }
        return m_textureMap[textureID].nFrames;
    }
    void clean();

    std::map<std::string, Texture> getTextureMap() const {
        return m_textureMap;
    }

  private:
    TextureManager(){};
    std::map<std::string, Texture> m_textureMap;
};

#endif
