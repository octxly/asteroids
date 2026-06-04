#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <Adafruit_SSD1306.h>
#include "Input/Joystick.h"
#include "Vector/Vector2.h"

class Player
{
    Joystick joystick;

    Vector2<int16_t> position;
    Vector2<int16_t> velocity;

public:
    bool queueBullet;
    bool inGrace;

    Player();

    void update();
    void render(Adafruit_SSD1306& display) const;
};

#endif //ASTEROIDS_PLAYER_H
