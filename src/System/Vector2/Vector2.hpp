#pragma once

#include <iostream>

template <typename T>
class Vector2
{
    public:
        Vector2() = default;
        Vector2(T x, T y) : x(x), y(y) {}
        ~Vector2() = default;

        T x;
        T y;

        Vector2<T> operator+(const Vector2<T>& other) const
        {
            return Vector2<T>(x + other.x, y + other.y);
        }

        Vector2<T> operator-(const Vector2<T>& other) const
        {
            return Vector2<T>(x - other.x, y - other.y);
        }

        Vector2<T> operator*(const T& scalar) const
        {
            return Vector2<T>(x * scalar, y * scalar);
        }

        Vector2<T> operator/(const T& scalar) const
        {
            return Vector2<T>(x / scalar, y / scalar);
        }

        Vector2<T>& operator+=(const Vector2<T>& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2<T>& operator-=(const Vector2<T>& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2<T>& operator*=(const T& scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2<T>& operator/=(const T& scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vector2<T>& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2<T>& other) const
        {
            return x != other.x || y != other.y;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector)
        {
            os << "Vector2(" << vector.x << ", " << vector.y << ")";
            return os;
        }
};