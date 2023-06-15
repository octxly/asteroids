#ifndef BULLET
#define BULLET

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Vector.cpp"
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class Bullet{
  private:
    Adafruit_SSD1306 *display;
    Vector2 pos;
    Vector2 dir;

    float speed = 100;
  
  public:
    bool markedDelete = false;
  
    Bullet(Adafruit_SSD1306 *display, Vector2 pos, Vector2 dir) : 
    display(display), pos(pos), dir(dir) {}

    Bullet(): display(0), pos(Vector2()), dir(Vector2()) {}

    void update(float deltaTime) {
      
      pos.x += dir.x * speed * (deltaTime / 1000.0);
      pos.y += dir.y * speed * (deltaTime / 1000.0);
      
      if(pos.x > SCREEN_WIDTH || pos.x < 0 || pos.y > SCREEN_HEIGHT || pos.y < 0) markedDelete = true;
    }
    
    void render() {
      display->drawPixel(pos.x, pos.y, 1);
    }
};

#endif
