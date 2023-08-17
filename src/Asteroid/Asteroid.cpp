#ifndef ASTEROID
#define ASTEROID

#include <Arduino.h>
#include "Vector.cpp"
#include "AsteroidParams.cpp"

struct Asteroid{
    Vector2S pos;
    Vector2S dir;

    uint8_t stage;

    // Vector2S vertices[8];
    short vMags[8];

    Asteroid(Vector2S pos = Vector2S(), Vector2S dir = Vector2S(), uint8_t stage = 0) : 
        pos(pos), dir(dir), stage(stage) {}
};

#endif