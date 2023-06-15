#pragma once

#include <string>

class LoaderParams final
{
public:
    LoaderParams(const int x, const int y, const int width, const int height);

    int x() const;
    int y() const;
    int width() const;
    int height() const;

private:
    int x_;
    int y_;

    int width_;
    int height_;
};
