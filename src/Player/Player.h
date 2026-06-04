#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include "Input/Joystick.h"

class Adafruit_SSD1306;
class Bullet;

class Player
{
    Joystick joystick;

    Vector2<int16> position;
    Vector2<int16> velocity;

public:
    bool queueBullet;
    bool inGrace;

    Player();

    void update();
    void render(Adafruit_SSD1306& display) const;

    Bullet generateBullet() const;
};

#endif //ASTEROIDS_PLAYER_H
