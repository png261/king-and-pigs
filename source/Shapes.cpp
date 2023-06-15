#include "Shapes.hpp"

#include <cmath>

Point::Point(const float x, const float y)
    : _x(x)
    , _y(y)
{}

Point::Point()
    : _x(0)
    , _y(0)
{}

float Point::x() const
{
    return _x;
}
float Point::y() const
{
    return _y;
};
void Point::setX(const float x)
{
    _x = x;
};
void Point::setY(const float y)
{
    _y = y;
};

Rectangle::Rectangle(const float x, const float y, const int width, const int height)
    : _x(x)
    , _y(y)
    , _width(width)
    , _height(height)
{
    update();
}

Rectangle::Rectangle()
    : _x(0)
    , _y(0)
    , _width(1)
    , _height(1)
{
    update();
}

Rectangle::Rectangle(Rectangle* const other)
{
    copy(other);
}

void Rectangle::copy(Rectangle* const other)
{
    _x = other->x();
    _y = other->y();
    _width = other->w();
    _height = other->h();

    update();
}

void Rectangle::addX(const float x)
{
    _x += x;

    update();
}

void Rectangle::addY(const float y)
{
    _y += y;

    update();
}

void Rectangle::setX(const float x)
{
    _x = x;

    update();
}
void Rectangle::setY(const float y)
{
    _y = y;

    update();
}

void Rectangle::stretch(const float scale)
{
    stretch(scale, scale);
}

void Rectangle::stretch(const float scaleX, const float scaleY)
{
    if ((scaleX <= 0) || (scaleY <= 0)) return;

    const float oldW = _width;
    const float oldH = _height;

    _width *= scaleX;
    _height *= scaleY;

    // Centralizing one rectangle on the other
    _x += std::abs(oldW - _width) * 0.5f;
    _y += std::abs(oldH - _height) * 0.5f;

    update();
}

void Rectangle::update()
{
    _top = _y;
    _bottom = _y + _height;
    _leftmost = _x;
    _rightmost = _x + _width;
    _center = Point(_x + (_width * 0.5f), _y + (_height * 0.5f));
    _topLeft = Point(_x, _y);
    _topRight = Point(_x + _width, _y);
    _bottomLeft = Point(_x, _y + _height);
    _bottomRight = Point(_x + _width, _y + _height);
    _topCenter = Point(_center.x(), _top);
    _bottomCenter = Point(_center.x(), _bottom);
    _leftCenter = Point(_leftmost, _center.y());
    _rightCenter = Point(_rightmost, _center.y());
}

float Rectangle::x() const
{
    return _x;
};
float Rectangle::y() const
{
    return _y;
};
int Rectangle::w() const
{
    return _width;
};
int Rectangle::h() const
{
    return _height;
};
float Rectangle::top() const
{
    return _top;
};
float Rectangle::bottom() const
{
    return _bottom;
};
float Rectangle::leftmost() const
{
    return _leftmost;
};
float Rectangle::rightmost() const
{
    return _rightmost;
};
Point Rectangle::center() const
{
    return _center;
};
Point Rectangle::leftCenter() const
{
    return _leftCenter;
};
Point Rectangle::rightCenter() const
{
    return _rightCenter;
};
Point Rectangle::topLeft() const
{
    return _topLeft;
};
Point Rectangle::topRight() const
{
    return _topRight;
};
Point Rectangle::topCenter() const
{
    return _topCenter;
};
Point Rectangle::bottomLeft() const
{
    return _bottomLeft;
};
Point Rectangle::bottomRight() const
{
    return _bottomRight;
};
Point Rectangle::bottomCenter() const
{
    return _bottomCenter;
};
