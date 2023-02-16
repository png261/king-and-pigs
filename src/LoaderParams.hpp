#ifndef LOADER_PARAMS
#define LOADER_PARAMS

#include <string>

class LoaderParams
{
public:
    LoaderParams(
        int x,
        int y,
        int width,
        int height,
        int textureWidth,
        int textureHeight,
        int numFrames,
        int lives = 0,
        int callbackID = 0,
        int textureX = 0,
        int textureY = 0);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getTextureWidth() const;
    int getTextureHeight() const;
    int getTextureX() const;
    int getTextureY() const;
    std::string getTextureID() const;
    int getNumFrames() const;
    int getLives() const;
    int getCallbackID() const;

private:
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_textureWidth;
    int m_textureHeight;
    int m_textureX;
    int m_textureY;

    int m_callbackID;

    int m_numFrames;

    int m_lives;
};

#endif
