#ifndef ASTEROIDS_JOYSTICK_H
#define ASTEROIDS_JOYSTICK_H

#include <stdint.h>
#include "Math/Vector2.h"

class Joystick
{
    Vector2<int8_t> value;
    bool actuated;

public:
    Joystick();

    void update();

    Vector2<int8_t> getNormalized() const
    {
        return value;
    }
    bool isActuated() const
    {
        return actuated;
    }
};

#endif //ASTEROIDS_JOYSTICK_H
