#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

class TextureManager {
  public:
    static TextureManager *Instance() {
        static TextureManager *s_pInstance = new TextureManager;
        return s_pInstance;
    }

    bool load(std::string filename, std::string textureID,
              SDL_Renderer *pRenderer, int nFrames = 1);
    void draw(std::string textureID, int x, int y, int width, int height,
              SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer *pRenderer,
                   double angle, int alpha = 255,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getNFrames(std::string textureID) {
        if (m_nFrameMap.find(textureID) == m_nFrameMap.end()) {
            return 1;
        }
        return m_nFrameMap[textureID];
    }
    void clean();

  private:
    TextureManager(){};
    std::map<std::string, SDL_Texture *> m_textureMap;
    std::map<std::string, int> m_nFrameMap;
};

#endif
