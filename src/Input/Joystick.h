//
// Created by julian on 2026-05-19.
//

#ifndef ASTEROIDS_JOYSTICK_H
#define ASTEROIDS_JOYSTICK_H

#include "Vector/Vector2.h"
#include <Arduino.h>

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
