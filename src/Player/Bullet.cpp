#ifndef BULLET
#define BULLET

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Vector2.cpp"
#include "Screendim.h"

#define SPEED 100

class Bullet{
    private:
        Vector2<uint8_t> pos; //only need 0-127 max = +255
        Vector2<int8_t> dir; // +/- 1.28 input value is normalized

    public:
        bool markedDelete = false;

        Bullet(Vector2<uint8_t> pos = Vector2<uint8_t>(), Vector2<int8_t> dir = Vector2<int8_t>()) :
            pos(pos), dir(dir) {}

        void update(float deltaTime){
            //Ceil is needed otherwise it would be stuck in a perpetual loop of adding < 0.5 and rounding down.
            pos.x += ceil(dir.x / 100.0 * SPEED * deltaTime);
            pos.y += ceil(dir.y / 100.0 * SPEED * deltaTime);
            
            //NOTE: can get rid of checking for 0. since its unsigned, integer overflow will make the first condition true
            //would lower readability tho
            if(pos.x >= SCREEN_WIDTH || pos.x == 0 || pos.y >= SCREEN_HEIGHT || pos.y == 0) markedDelete = true;
        }

        void render(Adafruit_SSD1306 *display) { display->drawPixel(pos.x, pos.y, 1); }
};

#endif