#ifndef ASTEROID
#define ASTEROID

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Vector/Vector2.cpp"
#include "Screendim.h"
#include "Asteroid/AsteroidParams.h"

class Asteroid{
    public:
        Vector2<int16_t> pos;
        Vector2<int8_t> dir; //normalized +/-1.27

        uint8_t stage = 0;
        int8_t rotationSpd = 0;
        uint16_t rotation = 0; // + 655.35
        bool markedDelete = false;

        uint8_t vMags[L_N_VERTEX]; // +25.5 

        Vector2<float> rotateAround(Vector2<float> point, uint16_t rot){
            float angleRad = radians(rot + (rotation / 100.0));

            float angleCos = cos(angleRad);
            float angleSin = sin(angleRad);
            
            float transX = point.x - pos.x / 100.0;
            float transY = point.y - pos.y / 100.0;
            
            return Vector2<float>(
                transX * angleCos - transY * angleSin + pos.x / 100.0, 
                transX * angleSin + transY * angleCos + pos.y / 100.0
            );
        }

        void calcMags(){
            uint8_t radius = stage ? S_RAD : L_RAD;

            for (uint8_t i = 0; i < (stage ? S_N_VERTEX : L_N_VERTEX); i++){
                vMags[i] = random((stage ? S_MIN_MAG : L_MIN_MAG) * radius * 2, (stage ? S_MAX_MAG : L_MAX_MAG) * radius * 2) / 2.0;
            }

            rotationSpd = random(SPIN_MAX) + 1;
 
            rotationSpd *= random(2) == 0 ? 1 : -1; //Randomize spin direction;
        }

        Asteroid(Vector2<int16_t> pos = Vector2<int16_t>(), Vector2<int8_t> dir = Vector2<int8_t>(), uint8_t stage = 0) :
            pos(pos), dir(dir), stage(stage) { calcMags(); }

        void update(float deltaTime){
            uint8_t speed = stage ? S_SPEED : L_SPEED;
            //Can skip decoding since its writing the product to a scaled int anyways.
            pos.x += dir.x * speed * deltaTime;
            pos.y += dir.y * speed * deltaTime;

            //Deletion maxRad has to be slightly larger because otherwise it interferes with spawning.
            float maxRad = L_RAD * L_MAX_MAG * 1.05;

            rotation += (rotationSpd * deltaTime) * 100;
            
            //would lower readability tho
            if(pos.x / 100.0 - maxRad >= SCREEN_WIDTH || pos.x / 100.0 + maxRad <= 0 || pos.y / 100.0 - maxRad >= SCREEN_HEIGHT || pos.y / 100.0 + maxRad <= 0) markedDelete = true;
        }
        void render(Adafruit_SSD1306 *display){
            uint16_t degInterval = 360.0 / (stage ? S_N_VERTEX : L_N_VERTEX);

            uint8_t nVert = stage ? S_N_VERTEX : L_N_VERTEX;

            //prev starts on the last one so it can be utilized by the first one.
            Vector2<float> prev = rotateAround(Vector2<float>(pos.x / 100.0, pos.y / 100.0 - vMags[nVert - 1]), degInterval * (nVert - 1));
            Vector2<float> current;

            for (uint8_t i = 0; i < nVert; i++){
                current = rotateAround(Vector2<float>(pos.x / 100.0, pos.y / 100.0 - vMags[i]), degInterval * i);

                display->drawLine(
                    current.x, current.y,
                    prev.x, prev.y,
                    1
                );
                prev = current;
            }
        }
};

#endif