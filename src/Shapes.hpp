#pragma once

class Point final
{
public:
    Point();
    Point(const float _x, const float _y);
    float x() const;
    float y() const;
    void setX(const float x);
    void setY(const float y);

private:
    float _x;
    float _y;
};

class Rectangle final
{
public:
    Rectangle();
    Rectangle(const Point topLeft, const Point bottomRight);
    Rectangle(Rectangle* const other);
    Rectangle(
        const float x,
        const float y,
        const int w,
        const int h,
        const float border_radius = 0);

    float x() const;
    float y() const;
    int w() const;
    int h() const;
    float border_radius() const;

    float top() const;
    float bottom() const;
    float leftmost() const;
    float rightmost() const;

    Point center() const;
    Point leftCenter() const;
    Point rightCenter() const;
    Point topLeft() const;
    Point topRight() const;
    Point topCenter() const;
    Point bottomLeft() const;
    Point bottomRight() const;
    Point bottomCenter() const;

    void copy(Rectangle* const other);
    void addX(const float x);
    void addY(const float y);
    void setX(const float x);
    void setY(const float y);
    void setBorderRadius(const float border_radius);
    void stretch(const float scale);
    void stretch(const float scaleX, const float scaleY);

    void update();

private:
    float _x;
    float _y;
    int _width;
    int _height;
    float _border_radius;

    float _top;
    float _bottom;
    float _leftmost;
    float _rightmost;

    Point _center;
    Point _leftCenter;
    Point _rightCenter;

    Point _topLeft;
    Point _topRight;
    Point _topCenter;
    Point _bottomLeft;
    Point _bottomRight;
    Point _bottomCenter;
};
