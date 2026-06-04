//
// Created by julian on 2026-05-26.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "AsteroidParams.h"
#include "Screendim.h"
#include "Vector/Vector2.h"
#include "Types.h"

class Adafruit_SSD1306;

class Asteroid
{
    Vector2<int16> position;
    Vector2<int8> velocity;

    uint8 vertexMagnitudes[L_N_VERTEX];

    uint8 stage;

    int8 rotationSpeed;
    uint8 rotation;

    void calcMags();

public:
    Asteroid();
    Asteroid(Vector2<int16> position, Vector2<int8> direction, uint8 stage);

    void update();
    void render(Adafruit_SSD1306& display) const;

    bool isOutOfBounds() const
    {
        return position.x < 0 || position.x > SCREEN_WIDTH || position.y < 0 || position.y > SCREEN_HEIGHT;
    }

    bool isActive() const
    {
        return velocity.x != 0 || velocity.y != 0;
    }

    void deactivate()
    {
        velocity.x = 0;
        velocity.y = 0;
    }
};

#endif //ASTEROIDS_ASTEROID_H
