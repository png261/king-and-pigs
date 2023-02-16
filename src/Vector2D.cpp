#include "Vector2D.hpp"

Vector2D::Vector2D(float x, float y)
    : m_x(x)
    , m_y(y)
{}

float Vector2D::getX() const
{
    return m_x;
}
float Vector2D::getY() const
{
    return m_y;
}

void Vector2D::setX(float x)
{
    m_x = x;
}

void Vector2D::setY(float y)
{
    m_y = y;
}

int Vector2D::length() const
{
    return sqrt(m_x * m_x + m_y * m_y);
}

Vector2D Vector2D::operator+(const Vector2D& v2) const
{
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
    return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;

    return v1;
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x -= v2.m_x;
    v1.m_y -= v2.m_y;

    return v1;
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;

    return *this;
}

Vector2D Vector2D::operator/(float scalar) const
{
    return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;

    return *this;
}

void Vector2D::normalize()
{
    int l = length();
    if (l > 0) {
        (*this) /= l;
    }
}
