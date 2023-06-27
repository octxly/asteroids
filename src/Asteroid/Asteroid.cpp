#ifndef ASTEROID
#define ASTEROID

#include "Vector.cpp"
#include "AsteroidParams.cpp"

struct Asteroid{
    Vector2 pos;
    Vector2 dir;

    // Vector2 rotDir;
    // float rotation;
    // float speed = 25;

    int stage;

    Vector2 vertices[8];

    bool markedDelete = false;

    Asteroid(Vector2 pos = Vector2(), Vector2 dir = Vector2(), int stage = 0) : 
        pos(pos), dir(dir), stage(stage) {}
};

#endif