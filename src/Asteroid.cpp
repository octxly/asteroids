#ifndef ASTEROID
#define ASTEROID

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Vector.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class Asteroid{
    private:
        Adafruit_SSD1306 *display;
        Vector2 pos;
        Vector2 dir;

        int stage;
        
        float speed = 20;

    public:
        bool markedDelete = false;

        Asteroid(Vector2 pos = Vector2(), Vector2 dir = Vector2(), int stage = 1) : pos(pos), dir(dir), stage(stage) {}

        void update(float deltaTime){
            deltaTime /= 1000.0;
            pos.x += dir.x * speed * deltaTime;
            pos.y += dir.y * speed * deltaTime;
            
            if(pos.x >= SCREEN_WIDTH || pos.x < 0 || pos.y >= SCREEN_HEIGHT || pos.y < 0) markedDelete = true;
        }

        void render(){
            
        }

        void onHit(){

        }
};

#endif