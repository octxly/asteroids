#ifndef ASTEROIDS_LED_H
#define ASTEROIDS_LED_H

#include <Arduino.h>
#include <stdint.h>
#include "Math/Trig.h"

constexpr uint8_t LED_PIN = 10;

inline void initLED()
{
    pinMode(LED_PIN, OUTPUT);
}

inline void tickLED(uint8_t lives)
{
    switch (lives)
    {
    case 3:                      //bitshift to divide time to increase period, add 32 to adjust for amplitude of wave, divide output to decrease brightness
        analogWrite(LED_PIN, (fastSine(millis() >> 4) + 32) >> 2);
        break;
    case 2:
        analogWrite(LED_PIN, (fastSine(millis() >> 2) + 32) >> 2);
        break;
    case 1:
        analogWrite(LED_PIN, (fastSine(millis()) + 32) >> 2);
        break;
    case 0:
        analogWrite(LED_PIN, 0);
        break;
    }
}

#endif //ASTEROIDS_LED_H
