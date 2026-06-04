//
// Created by julian on 2026-06-03.
//

#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H
#include "Vector/Vector2.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Screendim.h"

class Bullet
{
    Vector2<int16_t> position;
    Vector2<int8_t> velocity;

public:
    Bullet();
    Bullet(Vector2<int16_t> position, Vector2<int8_t> direction);

    void update();
    void render(Adafruit_SSD1306& display) const;

    bool isOutOfBounds() const
    {
        return position.x < 0 || position.x > SCREEN_WIDTH || position.y < 0 || position.y > SCREEN_HEIGHT;
    }

    bool isActive() const
    {
        return !(velocity.x == 0 && velocity.y == 0);
    }
};

#endif //ASTEROIDS_BULLET_H
