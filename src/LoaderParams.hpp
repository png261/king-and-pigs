#pragma once

#include <string>

class LoaderParams
{
public:
    LoaderParams(const int x, const int y, const int width, const int height);

    int x() const;
    int y() const;
    int width() const;
    int height() const;

private:
    int m_x;
    int m_y;

    int m_width;
    int m_height;
};
