#ifndef BUTTON
#define BUTTON

#include <Arduino.h>

class Button {
    private:
      int pin;
      int state = 0;
      
    public: 
      Button(int pin){
        pinMode(pin, INPUT);
        this->pin = pin;
      }

      int getState(){ return digitalRead(pin); }
};

#endif
