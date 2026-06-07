#ifndef ASTEROIDS_VECTOR2_H
#define ASTEROIDS_VECTOR2_H
#include <stdint.h>

template <typename T>
struct Vector2
{
    T x;
    T y;

    explicit Vector2(T x = 0, T y = 0) : x(x), y(y)
    {

    }


    Vector2 perpendicular() const
    {
        return Vector2(-y, x);
    }

    uint32_t lengthSquared() const
    {
        return x*x + y*y;
    }
};

#endif //ASTEROIDS_VECTOR2_H
