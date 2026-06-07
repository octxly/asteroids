#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Asteroid/Asteroid.h"
#include "Bullet/Bullet.h"
#include "Player/Player.h"

#define NUM_BULLETS 5
#define NUM_ASTEROIDS 17

#define FOREACH_ACTIVE(element, arr, active) \
    for (auto& (element) : (arr))\
        if (element.isActive() == (active))\

#define OLED_RESET -1 //idk but im supposed to do this
Adafruit_SSD1306 display(SCREEN_WIDTH_ACTUAL, SCREEN_HEIGHT_ACTUAL, &Wire, OLED_RESET);

Player player;

Bullet bullets[NUM_BULLETS];
Asteroid asteroids[NUM_ASTEROIDS];

unsigned long lastAstSpawn = 0;
unsigned long lastHit = 0;

uint8_t score = 0;
bool hasStarted = false;

// auto ledControl = LEDControl(10);

//delta time stuff
unsigned long frameTimer = 0;
unsigned long asteroidTimer = 0;

void setup() {
    //resetting the board (just in case)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(1);
    display.setTextSize(1);

    randomSeed(analogRead(A6));
}

void loop() {
    unsigned long now = millis();

    if (now - asteroidTimer >= AST_SPAWNRATE)
    {
        asteroidTimer = now;

        FOREACH_ACTIVE(asteroid, asteroids, false)
        {
            asteroid = Asteroid::spawnAsteroid();
            break;
        }
    }

    if (now - frameTimer >= 45) //20 fps
    {
        display.clearDisplay();

        display.setCursor(0, 0);
        display.println(now-frameTimer);

        frameTimer = now;

        player.update();

        if (player.queueBullet)
        {
            player.queueBullet = false;

            FOREACH_ACTIVE(bullet, bullets, false)
            {
                bullet = player.generateBullet();
                break;
            }
        }

        FOREACH_ACTIVE(bullet, bullets, true)
        {
            bullet.update();

            if (bullet.isOutOfBounds())
            {
                bullet.deactivate();
                continue;
            }

            FOREACH_ACTIVE(asteroid, asteroids, true)
            {
                if (asteroid.isIntersecting(bullet.getPosition()))
                {
                    if (asteroid.getStage() == ASTEROID_LARGE)
                    {
                        uint8_t numSplit = random(ASTEROID_NUM_SPLIT_MIN, ASTEROID_NUM_SPLIT_MAX + 1);
                        uint8_t currAdded = 0;

                        FOREACH_ACTIVE(newAsteroid, asteroids, false)
                        {
                            newAsteroid = asteroid.spawnBrokenChunk();
                            currAdded++;

                            if (currAdded == numSplit) break;
                        }
                    }

                    asteroid.deactivate();
                    bullet.deactivate();

                    break; //exit the loop for this iteration since the bullet is no longer valid, so dont check any other asteroids
                }
            }
        }

        FOREACH_ACTIVE(asteroid, asteroids, true)
        {
            asteroid.update();

            if (asteroid.isOutOfBounds())
            {
                asteroid.deactivate();
            }
        }


        player.render(display);

        FOREACH_ACTIVE(bullet, bullets, true)
            bullet.render(display);

        FOREACH_ACTIVE(asteroid, asteroids, true)
            asteroid.render(display);

        display.display();
    }
}