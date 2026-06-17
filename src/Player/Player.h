#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include "Input/Joystick.h"

class Adafruit_SSD1306;
class Bullet;

class Player
{
    Vector2<int16_t> position;
    Vector2<int16_t> velocity;

    Joystick joystick;

public:
    bool queueBullet;
    bool inGrace;

    uint8_t lives;

    Player();

    void update();
    void render(Adafruit_SSD1306& display) const;

    Bullet generateBullet() const;

    Vector2<int16_t> getPosition() const
    {
        return position;
    }
};

#endif //ASTEROIDS_PLAYER_H
