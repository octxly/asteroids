#include "Joystick.h"

#define PIN_X A6
#define PIN_Y A7

//Deadzone on the original analog scale of -512 to 511
#define DEADZONE_RANGE 50

//Input from analog read comes in as 0-1023, changes that to -8 - +8
inline int8_t remap(const int in)
{
    const int v = in - 511;

    // deadzone (adjust as needed)
    if (v > -DEADZONE_RANGE && v < DEADZONE_RANGE)
        return 0;

    return v >> 6; //Narrowing is fine due to such large bitshift
}

Joystick::Joystick() : value(0, -8), actuated(false)
{
    pinMode(PIN_X, INPUT);
    pinMode(PIN_Y, INPUT);
}

void Joystick::update()
{
    Vector2<int8_t> raw = Vector2<int8_t>(remap(analogRead(PIN_X)), remap(analogRead(PIN_Y)));

    if (raw.x == 0 && raw.y == 0)
    {
        actuated = false;
        return;
    }

    actuated = true;

    //ratio of target magnitude of 8.0 to the actual magnitude
    const float magCoefficient = 8.0 / sqrt(sq(raw.x) + sq(raw.y));

    this->value = Vector2<int8_t>(raw.x * magCoefficient, raw.y * magCoefficient);
}