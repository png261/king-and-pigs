#pragma once

class Point
{
public:
    float x;
    float y;
    Point();
    Point(const float x, const float y);
};

struct Rectangle
{
    float x;
    float y;
    int w;
    int h;

    float top;
    float bottom;
    float leftmost;
    float rightmost;

    Point center;
    Point leftCenter;
    Point rightCenter;

    Point topLeft;
    Point topRight;
    Point topCenter;
    Point bottomLeft;
    Point bottomRight;
    Point bottomCenter;

    Rectangle(const float x, const float y, const int w, const int h);
    Rectangle(const Point topLeft, const Point bottomRight);
    Rectangle(Rectangle* const other);
    Rectangle();
    void copy(Rectangle* const other);
    void addX(const float x);
    void addY(const float y);
    void setX(const float x);
    void setY(const float y);
    void stretch(const float scale);
    void stretch(const float scaleX, const float scaleY);
    void update();
};

struct Circle
{
    float x;
    float y;
    int r;
    float centerX;
    float centerY;
    Circle(const float x, const float y, const int r);
    void addX(const float x);
    void addY(const float y);
};
