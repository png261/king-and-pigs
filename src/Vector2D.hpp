#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

#include <cmath>

class Vector2D
{
public:
    Vector2D(float x = 0, float y = 0);

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);

    int length() const;

    Vector2D operator+(const Vector2D& v2) const;
    Vector2D operator-(const Vector2D& v2) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);
    Vector2D& operator*=(float scalar);
    Vector2D& operator/=(float scalar);

    void normalize();

    float m_x;
    float m_y;
};

#endif
