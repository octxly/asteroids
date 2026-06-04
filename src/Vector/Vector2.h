#ifndef ASTEROIDS_VECTOR2_H
#define ASTEROIDS_VECTOR2_H

template <typename T>
struct Vector2
{
    T x;
    T y;

    explicit Vector2(T x = 0, T y = 0) : x(x), y(y)
    {

    }


    Vector2 perpendicular()
    {
        return Vector2(-y, x);
    }

    // uint16_t lengthSquared()
    // {
    //     return sq(x) + sq(y);
    // }
};

#endif //ASTEROIDS_VECTOR2_H
