#ifndef VECTOR2
#define VECTOR2

//I'm not going to implement fixed-point float representation here for simplicity's sake
//Basic vector2 implementation. Template lets me specify what datatype the vector2 stores. Mostly used to switch between integer sizes.
template <typename T>
struct Vector2{
    T x;
    T y;

    Vector2(T x = 0, T y = 0) : x(x), y(y) {}
};

#endif