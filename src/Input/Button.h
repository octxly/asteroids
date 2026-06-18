#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

constexpr uint8_t lButtonPin = 2;
constexpr uint8_t rButtonPin = 3;

inline void initButtons()
{
    pinMode(lButtonPin, INPUT);
    pinMode(rButtonPin, INPUT);
}

inline bool readLButton()
{
    return digitalRead(lButtonPin);
}

inline bool readRButton()
{
    return digitalRead(rButtonPin);
}

#endif