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
        std::string textureID,
        int numFrames,
        int lives = 0,
        int callbackID = 0,
        int animSpeed = 0)
        : m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_textureWidth(textureWidth)
        , m_textureHeight(textureHeight)
        , m_textureID(textureID)
        , m_numFrames(numFrames)
        , m_lives(lives)
        , m_callbackID(callbackID)
        , m_animSpeed(animSpeed)
    {}

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getTextureWidth() const { return m_textureWidth; }
    int getTextureHeight() const { return m_textureHeight; }
    std::string getTextureID() const { return m_textureID; }
    int getNumFrames() const { return m_numFrames; }
    int getLives() const { return m_lives; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }

private:
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_textureWidth;
    int m_textureHeight;

    int m_callbackID;
    int m_animSpeed;

    std::string m_textureID;

    int m_numFrames;

    int m_lives;
};

#endif
