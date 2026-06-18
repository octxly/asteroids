#include "Player.h"
#include "Bullet/Bullet.h"
#include "Input/Button.h"
#include <Adafruit_SSD1306.h>

#define ACCEL 3
#define DECEL_COEFFICIENT 60 // this over /64 will be multiplied by each component of velocity to decelerate
#define DECEL_DENOMINATOR 6 //2^6 = 64
#define VELOCITY_FRAC 3
#define FIRE_RATE 500
// #define GRACE_PERIOD 3500 //milliseconds
#define NUM_LIVES 3

#define PLAYER_WIDTH 4
#define PLAYER_HEIGHT 6

#define BORDER_BUFFER 64

Player::Player() : position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), velocity(0, 0), queueBullet(false), inGrace(false), lives(NUM_LIVES)
{

}

void Player::update() {
    joystick.update();

    static bool hasFired = false;

    if (!queueBullet && readRButton() && !hasFired)
    {
        queueBullet = true;
        hasFired = true;
    } else if (!readRButton() && hasFired)
    {
        hasFired = false;
    }

    position.x += velocity.x >> VELOCITY_FRAC;
    position.y += velocity.y >> VELOCITY_FRAC;

    auto input = joystick.getNormalized();

    if (readLButton() && input.x != 0)
    {
        velocity.x += input.x * ACCEL;
    }
    else
    {
        //Don't need a set-to-zero for velocity due to natural floor division
        //Negative values result in ceil division, so change to positive for the operation
        if (velocity.x >= 0)
        {
            velocity.x = (velocity.x * DECEL_COEFFICIENT) >> DECEL_DENOMINATOR;
        } else
        {
            velocity.x = -((-velocity.x * DECEL_COEFFICIENT) >> DECEL_DENOMINATOR);
        }
    }
    if (readLButton() && input.y != 0)
    {
        velocity.y += input.y * ACCEL;
    }
    else
    {
        if (velocity.y >= 0)
        {
            velocity.y = (velocity.y * DECEL_COEFFICIENT) >> DECEL_DENOMINATOR;
        } else
        {
            velocity.y = -((-velocity.y * DECEL_COEFFICIENT) >> DECEL_DENOMINATOR);
        }
    }

    if (position.x < -BORDER_BUFFER)
    {
        position.x += SCREEN_WIDTH + BORDER_BUFFER * 2;
    } else if (position.x > SCREEN_WIDTH + BORDER_BUFFER)
    {
        position.x -= SCREEN_WIDTH + BORDER_BUFFER * 2;
    }

    if (position.y < -BORDER_BUFFER)
    {
        position.y += SCREEN_HEIGHT + BORDER_BUFFER * 2;
    } else if (position.y > SCREEN_HEIGHT + BORDER_BUFFER)
    {
        position.y -= SCREEN_HEIGHT + BORDER_BUFFER * 2;
    }
}

void Player::render(Adafruit_SSD1306& display) const
{
    auto up = joystick.getNormalized();
    auto right = up.perpendicular();

    auto topV = Vector2<int16_t>(SCALE_DOWN(position.x + up.x * PLAYER_HEIGHT), SCALE_DOWN(position.y + up.y * PLAYER_HEIGHT));
    auto leftV = Vector2<int16_t>(SCALE_DOWN(position.x - up.x * PLAYER_HEIGHT + right.x * PLAYER_WIDTH), SCALE_DOWN(position.y - up.y * PLAYER_HEIGHT + right.y * PLAYER_WIDTH));
    auto rightV = Vector2<int16_t>(SCALE_DOWN(position.x - up.x * PLAYER_HEIGHT - right.x * PLAYER_WIDTH), SCALE_DOWN(position.y - up.y * PLAYER_HEIGHT - right.y * PLAYER_WIDTH));

    display.fillTriangle(topV.x, topV.y, leftV.x, leftV.y, rightV.x, rightV.y, WHITE);
}

Bullet Player::generateBullet() const
{
    return {position, joystick.getNormalized()};
}
