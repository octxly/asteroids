//
// Created by julian on 2026-05-26.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include <Adafruit_SSD1306.h>
#include "AsteroidParams.h"
#include "Vector/Vector2.h"

class Asteroid
{
    Vector2<int16_t> position;
    Vector2<int8_t> velocity;

    uint8_t stage;

    int8_t rotationSpeed;
    uint8_t rotation;

    uint8_t vertexMagnitudes[L_N_VERTEX];

    void calcMags();

public:
    Asteroid(Vector2<int16_t> position, Vector2<int8_t> direction, uint8_t stage);

    void update();
    void render(Adafruit_SSD1306& display) const;

    bool isOutOfBounds() const
    {
        return false;
    }
};

#endif //ASTEROIDS_ASTEROID_H
