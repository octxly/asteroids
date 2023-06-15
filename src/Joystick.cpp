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
    Vector2 value;
  
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

    Vector2 getNormalized(){
      float magnitude = sqrt(value.x * value.x + value.y * value.y);

      return Vector2(value.x / magnitude, value.y / magnitude);
    }

    float getDeg(){
      if (value.x == 0 && value.y == 0) return -1; 
      
      float angleRad = atan2(value.x, -value.y);
      float angleDeg = (angleRad * 180.0 / PI);

      return angleDeg;
    }
};

#endif
