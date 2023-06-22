#ifndef ASTEROID
#define ASTEROID

#include <Adafruit_SSD1306.h>
#include "Vector.h"
#include <Arduino.h>
// #include "Vector.cpp"
// #include "AsteroidParams.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define magnitude(a1, a2) (sqrt(sq(a1) + sq(a2)))

class Asteroid{
    private:
        Adafruit_SSD1306 *display;
        Vector2 pos;
        Vector2 dir;

        // Vector2 dir;
        // Vector2 rotDir;
        // float rotation;
        // float speed = 25;

        // int stage;

        // Vector2 vertices[8];

        // Params stages[2] = { Params(8, 10, 0.65, 1.35), Params(6, 5, 0.65, 1.35) };

        // Vector2 rotateAround(Vector2 point, float deg){
        //     float angleRad = radians(deg);

        //     float angleCos = cos(angleRad);
        //     float angleSin = sin(angleRad);
            
        //     float rotatedX = point.x * angleCos - point.y * angleSin;
        //     float rotatedY = point.x * angleSin + point.y * angleCos;
            
        //     return Vector2(rotatedX, rotatedY);
        // }

    public:
        // bool markedDelete = false;

        Asteroid() {}
        // Asteroid(Adafruit_SSD1306 * display, Vector2 pos, Vector2 dir, int stage) : 
        //     display(display), pos(pos), dir(dir), stage(stage) { calcVertex(); }

        void update(float deltaTime){
            // deltaTime /= 1000.0;
            // pos.x += dir.x * speed * deltaTime;
            // pos.y += dir.y * speed * deltaTime;
            
            // if(pos.x >= SCREEN_WIDTH || pos.x < 0 || pos.y >= SCREEN_HEIGHT || pos.y < 0) markedDelete = true;

            // // rotation += atan2(rotDir.y, -rotDir.x);
        }

        void render(){
            // for (int i = 0; i < stages[stage].numVertex; ++i){
            //     Vector2 first = vertices[i];
            //     Vector2 last = i + 1 == stages[stage].numVertex ? vertices[0] : vertices[i + 1];

            //     Vector2 vc1 = Vector2(first.x + pos.x, first.y + pos.y);
            //     Vector2 vc2 = Vector2(last.x + pos.x, last.y + pos.y);

            //     display->drawLine(vc1.x, vc1.y, vc2.x, vc2.y, 1);
            // }
        }

        // void rotate(float rotation){
        //     this->rotation += rotation;

        //     for (int i = 0; i < stages[stage].numVertex; ++i)
        //         vertices[i] = rotateAround(vertices[i], this->rotation);
        // }

        // void calcVertex(){
        //     float degInterval = 360.0 / stages[stage].numVertex;

        //     int radius = stages[stage].radius;

        //     for (int i = 0; i < stages[stage].numVertex; ++i){
        //         Vector2 point = rotateAround(Vector2(0, -radius), degInterval * i);

        //         float magnitude = magnitude(point.x, point.y);
        //         float newMag = random(stages[stage].minMag * radius * 1000, stages[stage].maxMag * radius * 1000) / 1000.0;

        //         point.x *= newMag / magnitude;
        //         point.y *= newMag / magnitude;

        //         vertices[i] = point;
        //     }
        // }
};

#endif