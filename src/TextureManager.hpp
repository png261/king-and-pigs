#pragma once

#include <map>
#include <string>
#include "PhysicWorld.hpp"
#include "SDL.hpp"

class TextureManager final
{
public:
    static TextureManager* Instance();

    bool load(const std::string filename, const std::string textureID);

    void draw(
        const std::string textureID,
        const b2Vec2 position,
        const int width,
        const int height,
        const bool bFlipped = false);

    void drawFrame(
        const std::string id,
        const b2Vec2 position,
        const int width,
        const int height,
        const int currentRow,
        const int currentFrame,
        const float angle = 0,
        const bool bFlipped = false);

    void drawTile(
        const std::string id,
        const int margin,
        const int spacing,
        const b2Vec2 position,
        const int width,
        const int height,
        const int currentRow,
        const int currentFrame);

    void clean();

private:
    TextureManager();
    ~TextureManager();
    std::map<std::string, SDL_Texture*> m_textureMap;
};
