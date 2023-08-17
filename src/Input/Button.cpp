#ifndef BUTTON
#define BUTTON

#include <Arduino.h>

class Button{
    private:
      uint8_t pin;
      
    public: 
      Button(uint8_t pin){
        pinMode(pin, INPUT);
        this->pin = pin;
      }

      uint8_t getState(){ return digitalRead(pin); }
};

#endif