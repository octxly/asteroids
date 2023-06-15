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
  
    Vector2 top;
    Vector2 left;
    Vector2 right;

    Joystick *joystick;
    Button *btn1;
    Button *btn2;

    float accel = 50;
    float maxSpeed = 50;

    Vector2 vel;

    bool hasFired = false;

    void calcPoints(){
        top = Vector2(pos.x, pos.y - dim.y / 2);
        top = rotateAround(top);
        
        left = Vector2(pos.x + dim.x / 2, pos.y + dim.y / 2);
        left = rotateAround(left);
        
        right = Vector2(pos.x - dim.x / 2, pos.y + dim.y / 2);
        right = rotateAround(right);
    }
    
    Vector2 rotateAround(Vector2 point){
      float angleRad = rotation * PI / 180.0;
      
      float transX = point.x - pos.x;
      float transY = point.y - pos.y;
      
      float rotatedX = transX * cos(angleRad) - transY * sin(angleRad);
      float rotatedY = transX * sin(angleRad) + transY * cos(angleRad);
      
      return Vector2(rotatedX + pos.x, rotatedY + pos.y);
    }
    
  public:
    ArrayList<Bullet> bullets;
  
    Player(Adafruit_SSD1306 *display, Vector2 dimensions, Vector2 pos, float rotation, Joystick *joystick, Button *btn1, Button *btn2) : 
      display(display), dim(dimensions), pos(pos), rotation(rotation), joystick(joystick), btn1(btn1), btn2(btn2)
      { calcPoints(); }

    void render(){
      calcPoints();

      display->fillTriangle(
        top.x, top.y,
        left.x, left.y,
        right.x, right.y,
        1 
      );
    }
    void update(float deltaTime){
      if (joystick->getDeg() == -1) return; 
      
      rotation = joystick->getDeg();
      
//      if (btn1->getState()){
//      pos.x = max(min(pos.x + joystick->value.x * speed * (deltaTime / 1000.0), SCREEN_WIDTH), 0);
//
//      pos.y = max(min(pos.y + joystick->value.y * speed * (deltaTime / 1000.0), SCREEN_HEIGHT), 0);  
//      }

      vel.x = min(maxSpeed, vel.x + joystick->value.x * accel * (deltaTime / 1000.0));
      vel.y = min(maxSpeed, vel.y + joystick->value.y * accel * (deltaTime / 1000.0));

      pos.x = max(min(pos.x + vel.x * (deltaTime / 1000.0), SCREEN_WIDTH), 0);

      pos.y = max(min(pos.y + vel.y * (deltaTime / 1000.0), SCREEN_HEIGHT), 0); 
      
      if (btn2->getState() && !hasFired){
        hasFired = true;
        
        if (bullets.max > bullets.numElements) 
          bullets.add(Bullet(display, top, joystick->getNormalized()));
        
      }else if (!btn2->getState() && hasFired) hasFired = false;
    }
};

#endif
