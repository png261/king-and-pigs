#ifndef LOADER_PARAMS
#define LOADER_PARAMS

#include <string>

class LoaderParams
{
public:
    LoaderParams(
        const int x,
        const int y,
        const int width,
        const int height,
        const int textureWidth,
        const int textureHeight,
        const int textureX = 0,
        const int textureY = 0);

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    int textureWidth() const;
    int textureHeight() const;
    int textureX() const;
    int textureY() const;

private:
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_textureWidth;
    int m_textureHeight;
    int m_textureX;
    int m_textureY;
};

#endif
