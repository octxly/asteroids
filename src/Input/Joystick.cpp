#ifndef JOYSTICK
#define JOYSTICK

#include <Arduino.h>
#include "Vector2.cpp"

class Joystick{
    private:
        uint8_t pinX;
        uint8_t pinY;

        Vector2<float> value;

        float r(float in){
            float num = round((in / 512.0 - 1) * 20.0) / 20.0;
            
            return fabs(num) < 0.1f ? 0 : num;
        }

        void read(){
            this->value = Vector2<float>(r(analogRead(pinX)), r(analogRead(pinY)));
        }

    public:
        Joystick(uint8_t pinX, uint8_t pinY){
            pinMode(pinX, INPUT);
            pinMode(pinY, INPUT);

            this->pinX = pinX;
            this->pinY = pinY;
        }

        Vector2<float> readRaw(){
            read();

            return value;
        }

        Vector2<float> readNormalized(){
            read();
            float magnitude = sqrt(sq(value.x) + sq(value.y));

            return Vector2<float>(value.x / magnitude, value.y / magnitude);
        }

        float readDeg(){
            read();

            return degrees(atan2(value.x, -value.y));
        }

        bool xActuated(){
            read();

            return value.x != 0;
        }
        bool yActuated(){
            read();

            return value.y != 0;
        }
};

#endif