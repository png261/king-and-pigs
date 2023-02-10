#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <cmath>

class Vector2D
{
public:
    Vector2D(float x = 0, float y = 0)
        : m_x(x)
        , m_y(y)
    {}

    float getX() const { return m_x; }
    float getY() const { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    int length() const { return sqrt(m_x * m_x + m_y * m_y); }

    Vector2D operator+(const Vector2D& v2) const { return Vector2D(m_x + v2.m_x, m_y + v2.m_y); }
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;

        return v1;
    }

    Vector2D operator-(const Vector2D& v2) const { return Vector2D(m_x - v2.m_x, m_y - v2.m_y); }
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;

        return v1;
    }

    Vector2D operator*(float scalar) const { return Vector2D(m_x * scalar, m_y * scalar); }

    Vector2D& operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;

        return *this;
    }

    Vector2D operator/(float scalar) const { return Vector2D(m_x / scalar, m_y / scalar); }

    Vector2D& operator/=(float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;

        return *this;
    }

    void normalize()
    {
        int l = length();
        if (l > 0) {
            (*this) /= l;
        }
    }

    float m_x;
    float m_y;
};

#endif
