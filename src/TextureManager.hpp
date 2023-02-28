#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <map>
#include <string>
#include "Box2D.hpp"
#include "SDL.hpp"

class TextureManager
{
public:
    static TextureManager* Instance();

    bool load(std::string filename, std::string textureID);

    void draw(std::string textureID, b2Vec2 position, int width, int height, bool bFlipped = false);

    void drawFrame(
        std::string id,
        b2Vec2 position,
        int width,
        int height,
        int currentRow,
        int currentFrame,
        float angle = 0,
        bool bFlipped = false);
    void drawTile(
        std::string id,
        int margin,
        int spacing,
        b2Vec2 position,
        int width,
        int height,
        int currentRow,
        int currentFrame);
    void clean();

private:
    TextureManager(){};
    std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

#endif
