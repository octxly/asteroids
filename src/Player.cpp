#ifndef PLAYER
#define PLAYER

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Vector.cpp"
#include "./Input/Joystick.cpp"
#include "./Input/Button.cpp"
#include "ArrayList.cpp"
#include "./Bullet/BulletManager.cpp"
#include "./Bullet/Bullet.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define findLowest(a, b, c) (min(min((a), (b)), (c)))
#define findHighest(a, b, c) (max(max((a), (b)), (c)))
#define magnitude(a1, a2) (sqrt(sq(a1) + sq(a2)))

class Player {
  private:
    Adafruit_SSD1306 *display;
    
    Vector2S dim;
    Vector2S pos;
    Vector2F vel;
    float rotation;

    short accel = 50;
    short maxSpeed = 85;
    short decel = 30;
    float breakFactor = 1.2;

    Vector2S lastJoyPos = Vector2S(0, -1);

    Joystick *joystick;
    Button *btn1;
    Button *btn2;

    Vector2F rotateAround(Vector2S pivot, Vector2S point, float rotation){
      float angleRad = radians(rotation);

      float angleCos = cos(angleRad);
      float angleSin = sin(angleRad);
      
      float transX = point.getX() - pivot.getX();
      float transY = point.getY() - pivot.getY();
      
      float rotatedX = transX * angleCos - transY * angleSin;
      float rotatedY = transX * angleSin + transY * angleCos;
      
      return Vector2F(rotatedX + pivot.getX(), rotatedY + pivot.getY());
    }
    
  public:
    BulletManager bulletManager = BulletManager(display);
  
    Player(Adafruit_SSD1306 *display, Vector2S dimensions, Vector2S pos, float rotation, Joystick *joystick, Button *btn1, Button *btn2) : 
      display(display), dim(dimensions), pos(pos), rotation(rotation), joystick(joystick), btn1(btn1), btn2(btn2) {}

    void update(float deltaTime){
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


      pos.setX(vel.x * deltaTime);
      pos.setY(vel.y * deltaTime);
    
      pos.setX(fmod(pos.getX() + SCREEN_WIDTH, SCREEN_WIDTH));
      pos.setX(pos.getX() + pos.getX() < 0 ? SCREEN_WIDTH : 0);

      pos.setY(fmod(pos.getY() + SCREEN_HEIGHT, SCREEN_HEIGHT));
      pos.setY(pos.getX() + pos.getY() < 0 ? SCREEN_HEIGHT : 0);


      if (btn2->getState() && !hasFired && bulletManager.bullets.getMax() > bulletManager.bullets.getSize()){
        hasFired = true;
        
        bulletManager.bullets.add(Bullet(pos, lastJoyPos, magnitude));
      }else if (!btn2->getState() && hasFired) hasFired = false;
    }
    
    void render(){
      Vector2F top = rotateAround(pos, Vector2S(pos.getX(), pos.getY() - dim.getY() / 2), rotation);
      Vector2F left = rotateAround(pos, Vector2S(pos.getX() + dim.getX() / 2, pos.getY() + dim.getY() / 2), rotation);
      Vector2F right = rotateAround(pos, Vector2S(pos.getX() - dim.getX() / 2, pos.getY() + dim.getY() / 2), rotation);

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
