#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>

class TextureManager
{
public:
    static TextureManager* Instance();

    bool
    load(std::string filename, std::string textureID, SDL_Renderer* pRenderer, int nFrames = 1);

    void draw(
        std::string textureID,
        int x,
        int y,
        int width,
        int height,
        SDL_Renderer* pRenderer,
        bool bFlipped = false);

    void drawFrame(
        std::string id,
        int x,
        int y,
        int width,
        int height,
        int currentRow,
        int currentFrame,
        SDL_Renderer* pRenderer,
        bool bFlipped = false);
    void drawTile(
        std::string id,
        int margin,
        int spacing,
        int x,
        int y,
        int width,
        int height,
        int currentRow,
        int currentFrame,
        SDL_Renderer* pRenderer);
    int getNFrames(std::string textureID)
    {
        if (m_nFrameMap.find(textureID) == m_nFrameMap.end()) {
            return 1;
        }
        return m_nFrameMap[textureID];
    }
    void clean();

private:
    TextureManager(){};
    std::map<std::string, SDL_Texture*> m_textureMap;
    std::map<std::string, int> m_nFrameMap;
};

typedef TextureManager TheTextureManager;

#endif
