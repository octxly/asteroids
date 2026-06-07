#include "Bullet.h"
#include <Adafruit_SSD1306.h>

#define SPEED 5

Bullet::Bullet()
= default;

Bullet::Bullet(Vector2<int16_t> position, Vector2<int8_t> direction) : position(position), velocity(direction)
{

}

void Bullet::update()
{
    position.x += velocity.x * SPEED;
    position.y += velocity.y * SPEED;
}

void Bullet::render(Adafruit_SSD1306& display) const
{
    display.drawPixel(SCALE_DOWN(position.x), SCALE_DOWN(position.y), WHITE);
}
