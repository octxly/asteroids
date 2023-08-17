#ifndef JOYSTICK
#define JOYSTICK

#include <Arduino.h>
#include "Vector.cpp"

class Joystick {
  private:
    int pinX;
    int pinY;

    float r(float in){
      float num = round((in / 512.0 - 1) * 20.0) / 20.0;
      
      return fabs(num) < 0.1f ? 0 : num;
    }
  
  public:
    Vector2F value;
  
    Joystick(int analogX, int analogY){
      pinMode(analogX, INPUT);
      pinMode(analogY, INPUT);
    
      pinX = analogX;
      pinY = analogY;
    }
  
    void updateJoystick(){
      value.x = r(analogRead(pinX));
      value.y = r(analogRead(pinY));
    }

    Vector2S getNormalized(){
      float magnitude = sqrt(sq(value.x) + sq(value.y));

      return Vector2S(value.x / magnitude, value.y / magnitude);
    }

    float getDeg(){
      return value.x == 0 && value.y == 0 ? -1 : degrees(atan2(value.x, -value.y));
    }
};

#endif
