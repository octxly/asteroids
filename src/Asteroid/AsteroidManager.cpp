#ifndef ASTEROIDMANAGER
#define ASTEROIDMANAGER

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Vector.cpp"
#include "ArrayList.cpp"
#include "./Asteroid/Asteroid.cpp"
#include "./Asteroid/AsteroidParams.cpp"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define magnitude(a1, a2) (sqrt(sq(a1) + sq(a2)))


class AsteroidManager{
    private:
        Adafruit_SSD1306 *display;

        AsteroidParams stages[2] = { AsteroidParams(8, 10, 0.65, 1.35), AsteroidParams(6, 5, 0.65, 1.35) };


        // Vector2F rotateAround(Vector2S point, float deg){
        //     float angleRad = radians(deg);

        //     float angleCos = cos(angleRad);
        //     float angleSin = sin(angleRad);
            
        //     float rotatedX = point.x * angleCos - point.y * angleSin;
        //     float rotatedY = point.x * angleSin + point.y * angleCos;
            
        //     return Vector2(rotatedX, rotatedY);
        // }
 
        // void calcVertex(Vector2S vertices[], int stage){
        //     float degInterval = 360.0 / stages[stage].numVertex;

        //     int radius = stages[stage].radius;

        //     for (int i = 0; i < stages[stage].numVertex; ++i){
        //         Vector2S point = rotateAround(Vector2S(0, -radius), degInterval * i);

        //         float magnitude = magnitude(point.getX(), point.getY());
        //         float newMag = random(stages[stage].minMag * radius * 1000, stages[stage].maxMag * radius * 1000) / 1000.0;

        //         point.x *= newMag / magnitude;
        //         point.y *= newMag / magnitude;

        //         vertices[i] = point;
        //     }
        // }

    public:
        ArrayList<Asteroid, 10> asteroids;

        AsteroidManager(Adafruit_SSD1306 *display) : display(display) {}
};

#endif