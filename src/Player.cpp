#ifndef PLAYER
#define PLAYER

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Vector.cpp"
#include "Joystick.cpp"
#include "Button.cpp"
#include "ArrayList.cpp"
#include "Bullet.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class Player {
  private:
    Adafruit_SSD1306 *display;
    
    Vector2 dim;
    Vector2 pos;
    float rotation;
    Vector2 lastJoyPos;

    Joystick *joystick;
    Button *btn1;
    Button *btn2;

    float accel = 50;
    float maxSpeed = 50;
    float decel = 30;

    Vector2 vel;

    bool hasFired = false;
    
    Vector2 rotateAround(Vector2 point){
      float angleRad = radians(rotation);
      
      float transX = point.x - pos.x;
      float transY = point.y - pos.y;
      
      float rotatedX = transX * cos(angleRad) - transY * sin(angleRad);
      float rotatedY = transX * sin(angleRad) + transY * cos(angleRad);
      
      return Vector2(rotatedX + pos.x, rotatedY + pos.y);
    }
    
  public:
    ArrayList<Bullet> bullets;
  
    Player(Adafruit_SSD1306 *display, Vector2 dimensions, Vector2 pos, float rotation, Joystick *joystick, Button *btn1, Button *btn2) : 
      display(display), dim(dimensions), pos(pos), rotation(rotation), joystick(joystick), btn1(btn1), btn2(btn2) {}

    void render(){
      Vector2 top = rotateAround(Vector2(pos.x, pos.y - dim.y / 2));
      Vector2 left = rotateAround(Vector2(pos.x + dim.x / 2, pos.y + dim.y / 2));
      Vector2 right = rotateAround(Vector2(pos.x - dim.x / 2, pos.y + dim.y / 2));

      display->fillTriangle(
        top.x, top.y,
        left.x, left.y,
        right.x, right.y,
        1 
      );
    }
    void update(float deltaTime){
      deltaTime /= 1000.0;
      
      if (joystick->getDeg() != -1){ 
        rotation = joystick->getDeg();
        lastJoyPos = joystick->getNormalized();
      }


      float magnitude = sqrt(vel.x * vel.x + vel.y * vel.y);
      float decelRate = decel * deltaTime;
      float deMag = magnitude - decelRate;

      if (joystick->value.x != 0)
        vel.x += accel * joystick->value.x * deltaTime;
      else
        vel.x *= decelRate >= magnitude ? 0 : deMag / magnitude;

      if (joystick->value.y != 0)
        vel.y += accel * joystick->value.y * deltaTime;
      else
        vel.y *= decelRate >= magnitude ? 0 : deMag / magnitude;
      

      pos.x = max(min(pos.x + vel.x * deltaTime, SCREEN_WIDTH), 0);
      pos.y = max(min(pos.y + vel.y * deltaTime, SCREEN_HEIGHT), 0); 

      if (btn2->getState() && !hasFired && bullets.max > bullets.numElements){
        hasFired = true;

        bullets.add(Bullet(display, pos, lastJoyPos));
      }else if (!btn2->getState() && hasFired) hasFired = false;
    }
};

#endif
