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
      
      // void updateButton(){
      //   if (state == 0 && ) state = 1;
      //   else if (state == 1 && !digitalRead(pin)) state = 0;
      // }

      int getState(){ return digitalRead(pin); }
};

#endif
