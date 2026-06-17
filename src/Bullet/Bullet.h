#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

#include "Math/Vector2.h"
#include <stdint.h>
#include "Screendim.h"

class Adafruit_SSD1306;

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
        return velocity.x != 0 || velocity.y != 0;
    }

    void deactivate()
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    Vector2<int16_t> getPosition() const
    {
        return position;
    }
};

#endif //ASTEROIDS_BULLET_H
