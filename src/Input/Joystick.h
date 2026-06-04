#ifndef ASTEROIDS_JOYSTICK_H
#define ASTEROIDS_JOYSTICK_H

#include "Types.h"
#include "Vector/Vector2.h"

class Joystick
{
    Vector2<int8> value;
    bool actuated;

public:
    Joystick();

    void update();

    Vector2<int8> getNormalized() const
    {
        return value;
    }
    bool isActuated() const
    {
        return actuated;
    }
};

#endif //ASTEROIDS_JOYSTICK_H
