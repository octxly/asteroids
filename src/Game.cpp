#ifndef GAME
#define GAME

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Player/Player.cpp"
#include "List.cpp"
#include "Asteroid/Asteroid.cpp"
#include "Asteroid/AsteroidParams.h"
#include "Screendim.h"

class Game{
    private:
        Adafruit_SSD1306 *display; //gameobjects' render() take display pointer as an arguement cuz for some reason pointers are 8 bytes

        List<Asteroid, 15> asteroids = List<Asteroid, 15>();

        Player player = Player(Vector2<uint8_t>(8, 10), Vector2<float>(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0), 0);

        unsigned long lastAstSpawn = 0;
        uint16_t astInterval = SPAWNRATE * 1000;

    public:
        Game(Adafruit_SSD1306 *display) : display(display) {}

        void update(float deltaTime){
            if (millis() > lastAstSpawn + astInterval){
                spawnAsteroid();
                lastAstSpawn = millis();
            }

            //UPDATE - Update physics and variables.
            player.update(deltaTime);
            player.bullets.forEach([this, deltaTime](Bullet *element){
                element->update(deltaTime);

                if (element->markedDelete) player.bullets.remove(element);
            });
            asteroids.forEach([this, deltaTime](Asteroid *element){
                element->update(deltaTime);

                if (element->markedDelete) asteroids.remove(element);
            });

            //INSERT COLLISION CHECKING HERE

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
};

#endif