#ifndef ASTEROID
#define ASTEROID

#include <Arduino.h>
#include "Vector.cpp"

class Asteroid{
    private:
        Vector2 pos;
        Vector2 dir;

        int stage = 1;
        
        float speed = 20;

    public:
        bool markedDelete = false;

        // Asteroid() : pos(Vector2()), dir(Vector2()) {}
        Asteroid(Vector2 pos = Vector2(), Vector2 dir = Vector2()) : pos(pos), dir(dir){}

        void update(float deltaTime){

        }

        void render(){

        }

        void onHit(){

        }
};

#endif