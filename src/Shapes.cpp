#include "Shapes.hpp"
#include <cmath>

Point::Point(const float x, const float y)
    : x(x)
    , y(y)
{}

Point::Point()
    : x(0)
    , y(0)
{}


Rectangle::Rectangle(const float x, const float y, const int w, const int h)
    : x(x)
    , y(y)
    , w(w)
    , h(h)
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
    x += std::abs(oldW - w) / 2;
    y += std::abs(oldH - h) / 2;

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


Circle::Circle(const float x, const float y, const int r)
    : x(x)
    , y(y)
    , r(r)
{
    centerX = x + r;
    centerY = y + r;
}

void Circle::addX(const float _x)
{
    x += _x;
    centerX += x;
}

void Circle::addY(const float _y)
{
    y += _y;
    centerY += _y;
}
