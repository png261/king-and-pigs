#pragma once

class Point final
{
public:
    float x;
    float y;
    Point();
    Point(const float _x, const float _y);
};

class Rectangle final
{
public:
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

    Rectangle(const float _x, const float _y, const int _w, const int _h);
    Rectangle(const Point topLeft, const Point bottomRight);
    Rectangle(Rectangle* const other);
    Rectangle();
    void copy(Rectangle* const other);
    void addX(const float _x);
    void addY(const float _y);
    void setX(const float _x);
    void setY(const float _y);
    void stretch(const float scale);
    void stretch(const float scaleX, const float scaleY);
    void update();
};
