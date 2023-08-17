#ifndef BULLET
#define BULLET

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Vector.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

struct Bullet {
  Vector2S pos;
  Vector2S dir;

  uint8_t speed = 100;
  
  Bullet(Vector2S pos = Vector2S(), Vector2S dir = Vector2S(), uint8_t plrSpeed = 0) : 
    pos(pos), dir(dir) { this->speed += plrSpeed; }
};

#endif
