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

#define findLowest(a, b, c) (a<b?a:b<c?b:c)
#define findHighest(a, b, c) (a>b?a:b>c?b:c)
#define magnitude(a1, a2) (sqrt(sq(a1) + sq(a2)))

class Player {
  private:
    Adafruit_SSD1306 *display;
    
    Vector2 dim;
    Vector2 pos;
    Vector2 vel;
    float rotation;

    float accel = 50;
    float maxSpeed = 85;
    float decel = 30;
    float breakFactor = 1.2;

    Vector2 lastJoyPos = Vector2(0, -1);

    Joystick *joystick;
    Button *btn1;
    Button *btn2;
    
    Vector2 rotateAround(Vector2 point){
      float angleRad = radians(rotation);

      float angleCos = cos(angleRad);
      float angleSin = sin(angleRad);
      
      float transX = point.x - pos.x;
      float transY = point.y - pos.y;
      
      float rotatedX = transX * angleCos - transY * angleSin;
      float rotatedY = transX * angleSin + transY * angleCos;
      
      return Vector2(rotatedX + pos.x, rotatedY + pos.y);
    }
    
  public:
    ArrayList<Bullet, 10> bullets;
  
    Player(Adafruit_SSD1306 *display, Vector2 dimensions, Vector2 pos, float rotation, Joystick *joystick, Button *btn1, Button *btn2) : 
      display(display), dim(dimensions), pos(pos), rotation(rotation), joystick(joystick), btn1(btn1), btn2(btn2) {}

    void update(float deltaTime){
      deltaTime /= 1000.0;

      static bool hasFired = false;
      
      if (joystick->getDeg() != -1){ 
        rotation = joystick->getDeg();
        lastJoyPos = joystick->getNormalized();
      }


      float magnitude = magnitude(vel.x, vel.y);
      float decelRate = decel * deltaTime;
      float deMag = magnitude - decelRate;

      bool breakOn = btn1->getState();

      if (joystick->value.x != 0 && !breakOn)
        vel.x += accel * joystick->value.x * deltaTime;
      else
        vel.x *= (decelRate >= magnitude ? 0 : deMag / magnitude) / (breakOn ? breakFactor : 1);

      if (joystick->value.y != 0 && !breakOn)
        vel.y += accel * joystick->value.y * deltaTime;
      else
        vel.y *= (decelRate >= magnitude ? 0 : deMag / magnitude) / (breakOn ? breakFactor : 1);


      magnitude = magnitude(vel.x, vel.y);
      if (magnitude > maxSpeed){
        vel.x *= maxSpeed / magnitude;
        vel.y *= maxSpeed / magnitude;
      }
      magnitude = magnitude(vel.x, vel.y);


      pos.x += vel.x * deltaTime;
      pos.y += vel.y * deltaTime;
      
      pos.x = fmod(pos.x + SCREEN_WIDTH, SCREEN_WIDTH);
      pos.x += pos.x < 0 ? SCREEN_WIDTH : 0;

      pos.y = fmod(pos.y + SCREEN_HEIGHT, SCREEN_HEIGHT);
      pos.y += pos.y < 0 ? SCREEN_HEIGHT : 0;


      if (btn2->getState() && !hasFired && bullets.getMax() > bullets.getSize()){
        hasFired = true;
        
        bullets.add(Bullet(display, pos, lastJoyPos, magnitude));
      }else if (!btn2->getState() && hasFired) hasFired = false;
    }
    
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

      bool wrapX = findLowest(top.x, left.x, right.x) < 0 || findHighest(top.x, left.x, right.x) >= SCREEN_WIDTH;
      bool wrapY = findLowest(top.y, left.y, right.y) < 0 || findHighest(top.y, left.y, right.y) >= SCREEN_HEIGHT;
      
      if (wrapX || wrapY){
        int xOffset = wrapX ? (findLowest(top.x, left.x, right.x) < 0 ? SCREEN_WIDTH : -SCREEN_WIDTH) : 0;
        int yOffset = wrapY ? (findLowest(top.y, left.y, right.y) < 0 ? SCREEN_HEIGHT : -SCREEN_HEIGHT) : 0;

        display->fillTriangle(
          top.x + xOffset, top.y + yOffset,
          left.x + xOffset, left.y + yOffset,
          right.x + xOffset, right.y + yOffset,
          1
        );
      }
    }
};

#endif
