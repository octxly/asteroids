#ifndef BULLET
#define BULLET

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Vector.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

struct Bullet {
  Vector2 pos;
  Vector2 dir;

  float speed = 100;

  bool markedDelete = false;
  
  Bullet(Vector2 pos = Vector2(), Vector2 dir = Vector2(), float plrSpeed = 0) : 
    pos(pos), dir(dir) { this->speed += plrSpeed; }
};

#endif
