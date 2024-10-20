#ifndef GAME
#define GAME

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Player/Player.cpp"
#include "Input/Joystick.cpp"
#include "Input/Button.cpp"
#include "List.cpp"
#include "Asteroid/Asteroid.cpp"
#include "Asteroid/AsteroidParams.h"
#include "Ouput/Led.cpp"
#include "Ouput/Button.h"
#include "Screendim.h"

#define magnitude(a1, a2) (sqrt(sq((a1)) + sq((a2))))

class Game{
    public:
        Adafruit_SSD1306 *display; //gameobjects' render() take display pointer as an arguement cuz for some reason pointers are 8 bytes

        List<Asteroid, 11> asteroids;

        Player player = Player(Vector2<uint8_t>(8, 10), Vector2<float>(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0));

        unsigned long lastAstSpawn = 0;
        uint16_t astInterval = AST_SPAWNRATE * 1000;

        uint16_t score = 0;
        bool hasStarted = false;
        
        LEDControl ledControl = LEDControl(10);

        Game(Adafruit_SSD1306 *display) : display(display) {}

        Vector2<float> rotateAround(Vector2<float> point, uint16_t rotation){
            float angleRad = radians(rotation);

            float angleCos = cos(angleRad);
            float angleSin = sin(angleRad);

            return Vector2<float>(
                point.x * angleCos - point.y * angleSin, 
                point.x * angleSin + point.y * angleCos
            );
        }

        void update(float deltaTime){
            display->setCursor(0, 0);
            display->print(score);

            if (!hasStarted){
                drawCentreString(true);
                if (digitalRead(BTN1) || digitalRead(BTN2))
                    hasStarted = true;
                return;
            }
            if (ledControl.lives <= 0){
                drawCentreString(false);
                ledControl.update();
                return;
            }

            if (millis() > lastAstSpawn + astInterval){
                spawnAsteroid();
                lastAstSpawn = millis();
            }

            //UPDATE - Update physics and variables.
            player.update(deltaTime);
            player.bullets.forEach([this, deltaTime](Bullet *bullet){
                bullet->update(deltaTime);

                if (bullet->markedDelete) player.bullets.remove(bullet);
                else checkAsteroidCollisions(bullet);
            });
            asteroids.forEach([this, deltaTime](Asteroid *element){
                element->update(deltaTime);

                if (element->markedDelete) asteroids.remove(element);
                else{
                    //Player collisions
                    float distance = magnitude(element->pos.x / 100.0 - player.pos.x, element->pos.y / 100.0 - player.pos.y);

                    if (distance < (element->stage ? S_RAD : L_RAD) + player.dim.x / 2){
                        asteroids.remove(element);
                        ledControl.lives--;
                        tone(8, 200, 150);
                    }  
                }
            });

            ledControl.update();

            //RENDER - Actually draw things on screen.
            player.render(display);
            player.bullets.forEach([this](Bullet *element){
                element->render(display);
            });
            asteroids.forEach([this](Asteroid *element){
                element->render(display);
            });
        }

        void spawnAsteroid(){
            Vector2<int16_t> position;
            Vector2<int16_t> destination;

            uint8_t maxRad = ceil(L_MAX_MAG * L_RAD);

            switch(random(4)){
                case 0: //Top edge
                    position = Vector2<int16_t>(random(SCREEN_WIDTH) * 100, -maxRad * 100);
                    destination = Vector2<int16_t>(random(SCREEN_WIDTH), SCREEN_HEIGHT);
                break;
                    
                case 1: //Bottom edge
                    position = Vector2<int16_t>(random(SCREEN_WIDTH) * 100, (SCREEN_HEIGHT + maxRad) * 100);
                    destination = Vector2<int16_t>(random(SCREEN_WIDTH), 0);
                break;

                case 2: //Left edge
                    position = Vector2<int16_t>(-maxRad * 100, random(SCREEN_HEIGHT) * 100);
                    destination = Vector2<int16_t>(SCREEN_WIDTH, random(SCREEN_HEIGHT));
                break;

                case 3: //Right edge
                    position = Vector2<int16_t>((SCREEN_WIDTH + maxRad) * 100, random(SCREEN_HEIGHT) * 100);
                    destination = Vector2<int16_t>(0, random(SCREEN_HEIGHT));
                break;
            }
            
            //Generate direction from normalized displacement vector.
            Vector2<float> direction = normalize(Vector2<float>(destination.x - position.x / 100.0, destination.y - position.y / 100.0));

            uint8_t asteroidSpawnChance = random(S_SP_FREQ + L_SP_FREQ);
            asteroids.add(Asteroid(position, Vector2<int8_t>(direction.x * 100, direction.y * 100), asteroidSpawnChance < S_SP_FREQ));
        }
        Vector2<float> normalize(Vector2<float> in){
            float magnitude = sqrt(sq(in.x) + sq(in.y));

            return Vector2<float>(in.x / magnitude, in.y / magnitude);
        }

        void checkAsteroidCollisions(Bullet *bullet){
            asteroids.forEach([this, bullet](Asteroid *asteroid){
                //Bullet collisions with asteroids
                float distance = magnitude(asteroid->pos.x / 100.0 - bullet->pos.x, asteroid->pos.y / 100.0 - bullet->pos.y);

                //If measured distance is smaller than asteroid radius
                if (distance < (asteroid->stage ? S_RAD : L_RAD)){
                    if (asteroid->stage){ 
                        asteroids.remove(asteroid);
                        score += S_POINTS;
                    } else {
                        //First random direction
                        Vector2<float> newDir1 = rotateAround(
                            Vector2<float>(asteroid->dir.x / 100.0, asteroid->dir.y / 100.0),
                            random(SPLIT_DIFF)
                        );

                        //Second random direction
                        Vector2<float> newDir2 = rotateAround(
                            Vector2<float>(asteroid->dir.x / 100.0, asteroid->dir.y / 100.0),
                            -random(SPLIT_DIFF)
                        );

                        //Changing first asteroid
                        asteroid->dir = Vector2<int8_t>(newDir1.x * 100, newDir1.y * 100);
                        asteroid->stage = 1;
                        asteroid->calcMags();

                        //Adding another split asteroid
                        asteroids.add(Asteroid(
                            asteroid->pos,
                            Vector2<int8_t>(newDir2.x * 100, newDir2.y * 100),
                            1
                        ));

                        score += L_POINTS;
                    }

                    //Destroy bullet
                    player.bullets.remove(bullet);

                    tone(8, 300, 100);
                }
            });
        }

        //The boolean is a workaround so I can save the strings in flash instead of RAM.
        void drawCentreString(bool winMsg){ 
            const __FlashStringHelper* msg1 = F(" Press btn to start");
            // const char* msg1 = " Press";
            const __FlashStringHelper* msg2 = F(" You died");
            // const char* msg2 = " Dead";

            // int16_t x1, y1;
            // uint16_t w, h;
            // display->getTextBounds(winMsg ? msg1 : msg2, 0, 0, &x1, &y1, &w, &h);

            // display->setCursor(SCREEN_WIDTH / 2 - w / 2, SCREEN_HEIGHT / 2 - h / 2);
            display->print(winMsg ? msg1 : msg2);
        }
};

#endif