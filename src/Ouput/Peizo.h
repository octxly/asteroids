#ifndef ASTEROIDS_PEIZO_H
#define ASTEROIDS_PEIZO_H

#include <Arduino.h>

constexpr uint8_t PIEZO_PIN = 8;

inline void initPiezo()
{
    pinMode(PIEZO_PIN, OUTPUT);
}

inline void toneShot()
{
    tone(PIEZO_PIN, 400, 50);
}

inline void toneAsteroidHit()
{
    tone(PIEZO_PIN, 200, 50);
}

inline void tonePlayerHit()
{
    tone(PIEZO_PIN, 100, 500);
}

#endif //ASTEROIDS_PEIZO_H
