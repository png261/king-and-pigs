#include "Shapes.hpp"

#include <cmath>

Point::Point(const float _x, const float _y)
    : x(_x)
    , y(_y)
{}

Point::Point()
    : x(0)
    , y(0)
{}


Rectangle::Rectangle(const float _x, const float _y, const int _w, const int _h)
    : x(_x)
    , y(_y)
    , w(_w)
    , h(_h)
{
    update();
}

Rectangle::Rectangle()
    : x(0)
    , y(0)
    , w(1)
    , h(1)
{
    update();
}

Rectangle::Rectangle(Rectangle* const other)
{
    copy(other);
}

void Rectangle::copy(Rectangle* const other)
{
    x = other->x;
    y = other->y;
    w = other->w;
    h = other->h;

    update();
}

void Rectangle::addX(const float _x)
{
    x += _x;

    update();
}

void Rectangle::addY(const float _y)
{
    y += _y;

    update();
}

void Rectangle::setX(const float _x)
{
    x = _x;

    update();
}
void Rectangle::setY(const float _y)
{
    y = _y;

    update();
}

void Rectangle::stretch(const float scale)
{
    stretch(scale, scale);
}

void Rectangle::stretch(const float scaleX, const float scaleY)
{
    if ((scaleX <= 0) || (scaleY <= 0)) return;

    const float oldW = w;
    const float oldH = h;

    w *= scaleX;
    h *= scaleY;

    // Centralizing one rectangle on the other
    x += std::abs(oldW - w) / 2.0f;
    y += std::abs(oldH - h) / 2.0f;

    update();
}

void Rectangle::update()
{
    top = y;
    bottom = y + h;

    leftmost = x;
    rightmost = x + w;

    center = Point(x + (w / 2.0f), y + (h / 2.0f));

    topLeft = Point(x, y);
    topRight = Point(x + w, y);
    bottomLeft = Point(x, y + h);
    bottomRight = Point(x + w, y + h);

    topCenter = Point(center.x, top);
    bottomCenter = Point(center.x, bottom);
    leftCenter = Point(leftmost, center.y);
    rightCenter = Point(rightmost, center.y);
}
