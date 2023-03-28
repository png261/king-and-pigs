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
    this->update();
}

Rectangle::Rectangle()
    : x(0)
    , y(0)
    , w(1)
    , h(1)
{
    this->update();
}

Rectangle::Rectangle(Rectangle* const other)
{
    this->copy(other);
}

void Rectangle::copy(Rectangle* const other)
{
    this->x = other->x;
    this->y = other->y;
    this->w = other->w;
    this->h = other->h;

    this->update();
}

void Rectangle::addX(const float x)
{
    this->x += x;

    this->update();
}

void Rectangle::addY(const float y)
{
    this->y += y;

    this->update();
}

void Rectangle::setX(const float x)
{
    this->x = x;

    this->update();
}
void Rectangle::setY(const float y)
{
    this->y = y;

    this->update();
}

void Rectangle::stretch(const float scale)
{
    this->stretch(scale, scale);
}

void Rectangle::stretch(const float scaleX, const float scaleY)
{
    if ((scaleX <= 0) || (scaleY <= 0)) return;

    const float oldW = this->w;
    const float oldH = this->h;

    this->w *= scaleX;
    this->h *= scaleY;

    // Centralizing one rectangle on the other
    this->x += std::abs(oldW - this->w) / 2;
    this->y += std::abs(oldH - this->h) / 2;

    this->update();
}

void Rectangle::update()
{
    this->top = y;
    this->bottom = y + h;

    this->leftmost = x;
    this->rightmost = x + w;

    this->center = Point(x + (w / 2.0f), y + (h / 2.0f));

    this->topLeft = Point(x, y);
    this->topRight = Point(x + w, y);
    this->bottomLeft = Point(x, y + h);
    this->bottomRight = Point(x + w, y + h);

    this->topCenter = Point(center.x, top);
    this->bottomCenter = Point(center.x, bottom);
    this->leftCenter = Point(leftmost, center.y);
    this->rightCenter = Point(rightmost, center.y);
}


Circle::Circle(const float x, const float y, const int r)
    : x(x)
    , y(y)
    , r(r)
{
    this->centerX = x + r;
    this->centerY = y + r;
}

void Circle::addX(const float x)
{
    this->x += x;
    this->centerX += x;
}

void Circle::addY(const float y)
{
    this->y += y;
    this->centerY += y;
}
