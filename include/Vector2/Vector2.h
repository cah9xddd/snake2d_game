#pragma once
template<typename T>
struct Vector2
{
    Vector2() {};
    Vector2(T xx, T yy) : x(xx) , y (yy) {};
    T x = 0;
    T y = 0;
};