#include "Vector.h"
#include <cmath>

// Create Vector with (x, y)
Vector::Vector(float init_x, float init_y)
    : m_x(init_x), m_y(init_y)
{
}

// Create default Vector (0, 0)
Vector::Vector()
    : m_x(0.0f), m_y(0.0f)
{
}

// Set horizontal component
void Vector::setX(float new_x)
{
    m_x = new_x;
}

// Get horizontal component
float Vector::getX() const
{
    return m_x;
}

// Set vertical component
void Vector::setY(float new_y)
{
    m_y = new_y;
}

// Get vertical component
float Vector::getY() const
{
    return m_y;
}

// Set both components
void Vector::setXY(float new_x, float new_y)
{
    m_x = new_x;
    m_y = new_y;
}

// Return vector magnitude
float Vector::getMagnitude() const
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

// Normalize vector
void Vector::normalize()
{
    float magnitude = getMagnitude();

    // Avoid dividing by zero
    if (magnitude != 0.0f)
    {
        m_x /= magnitude;
        m_y /= magnitude;
    }
}

// Scale vector
void Vector::scale(float s)
{
    m_x *= s;
    m_y *= s;
}

// Add two Vectors
Vector Vector::operator+(const Vector& other) const
{
    return Vector(m_x + other.m_x, m_y + other.m_y);
}
