#pragma once
#include <cmath>
#include <iostream>
template<typename T>
struct Vector2
{
    explicit Vector2(T xx = {}, T yy = {}) : x(xx) , y (yy) {};
    
    T x = 0;
    T y = 0;
    T getLenght() const;

    
};
template <typename T>
Vector2<T> operator+(const Vector2<T>& V1, const Vector2<T>& V2) 
{
    return Vector2<T>(V1.x + V2.x, V1.y + V2.y);
}
template <typename T, typename B>
Vector2<T> operator+(const Vector2<T>& V1, const Vector2<B>& V2)
{
    return Vector2<T>(V1.x + (T)V2.x, V1.y + (T)V2.y);
}
template <typename T>
Vector2<T> operator-(const Vector2<T>& V1, const Vector2<T>& V2)
{
    return Vector2<T>(V1.x - V2.x, V1.y - V2.y);
}
template <typename T>
Vector2<T> operator*(const Vector2<T>& V1, const Vector2<T>& V2)
{
    return Vector2<T>(V1.x * V2.x, V1.y * V2.y);
}
template <typename T, typename B>
Vector2<T> operator*(const Vector2<T>& V1, B a)
{
    return Vector2<T>(V1.x * a, V1.y * a);
}
template <typename T, typename B>
Vector2<T> operator/(const Vector2<T>& V1, B a)
{
    return Vector2<T>(V1.x / a, V1.y / a);
}
template <typename T>
bool operator==(const Vector2<T>& V1, const Vector2<T>& V2)
{
    return (V1.x == V2.x && V1.y == V2.y);
}
template <typename T>
bool operator!=(const Vector2<T>& V1, const Vector2<T>& V2)
{
    return !(V1 == V2);
}
template <typename T>
inline T Vector2<T>::getLenght() const
{
    return T(sqrt(x * x + y * y));
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const  Vector2<T>& V)
{
    out << V.x << "/" << V.y << std::endl;
    return out;
}
