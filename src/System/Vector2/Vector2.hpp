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

template <typename T>
class Vector3 {
    public:
        Vector3() = default;
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        Vector3(glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) {}
        ~Vector3() = default;

        T x;
        T y;
        T z;

        Vector3<T> operator+(const Vector3<T>& other) const
        {
            return Vector3<T>(x + other.x, y + other.y, z + other.z);
        }

        Vector3<T> operator-(const Vector3<T>& other) const
        {
            return Vector3<T>(x - other.x, y - other.y, z - other.z);
        }

        Vector3<T> operator*(const T& scalar) const
        {
            return Vector3<T>(x * scalar, y * scalar, z * scalar);
        }

        Vector3<T> operator/(const T& scalar) const
        {
            return Vector3<T>(x / scalar, y / scalar, z / scalar);
        }

        Vector3<T>& operator+=(const Vector3<T>& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3<T>& operator-=(const Vector3<T>& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3<T>& operator*=(const T& scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vector3<T>& operator/=(const T& scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        bool operator==(const Vector3<T>& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const Vector3<T>& other) const
        {
            return x != other.x || y != other.y || z != other.z;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector)
        {
            os << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
            return os;
        }
};