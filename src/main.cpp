#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Asteroid/Asteroid.h"
#include "Bullet/Bullet.h"
#include "Input/Button.h"
#include "Ouput/Led.h"
#include "Ouput/Peizo.h"
#include "Player/Player.h"

#define NUM_BULLETS 5
#define NUM_ASTEROIDS 18

#define FOREACH_ACTIVE(element, arr, active) \
    for (auto& element : arr)\
        if (element.isActive() == (active))\

Adafruit_SSD1306 display(SCREEN_WIDTH_ACTUAL, SCREEN_HEIGHT_ACTUAL, &Wire, -1);

Player player;
Bullet bullets[NUM_BULLETS];
Asteroid asteroids[NUM_ASTEROIDS];

//delta time stuff
uint32_t frameTimer = 0;
uint32_t asteroidTimer = 0;

uint8_t score = 0;
bool hasStarted = false;

void setup() {
    //resetting the board (just in case)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(1);
    display.setTextSize(1);

    initButtons();
    initPiezo();
    initLED();

    randomSeed(analogRead(A6));

    display.clearDisplay();
    display.setCursor(0, 24);
    display.println(F("Press any button"));
    display.println(F("to start the game"));
    display.display();
}

void loop() {
    uint32_t now = millis();

    if (!hasStarted)
    {
        if (readLButton() || readRButton())
            hasStarted = true;

        return;
    }

    if (player.lives <= 0)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(F("You lost lmao"));
        display.display();

        return;
    }

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
        display.print(F("Score: "));
        display.print(score);
        display.setCursor(SCREEN_WIDTH_ACTUAL - 12, 0);
        display.print(now-frameTimer);

        frameTimer = now;

        player.update();

        if (player.queueBullet)
        {
            player.queueBullet = false;

            FOREACH_ACTIVE(bullet, bullets, false)
            {
                bullet = player.generateBullet();
                toneShot();
                break;
            }
        }

        FOREACH_ACTIVE(bullet, bullets, true)
        {
            bullet.update();

            if (bullet.isOutOfBounds())
            {
                bullet.deactivate();
            }
        }

        FOREACH_ACTIVE(asteroid, asteroids, true)
        {
            asteroid.update();

            if (asteroid.isOutOfBounds())
            {
                asteroid.deactivate();
                continue;
            }

            if (asteroid.isIntersecting(player.getPosition()))
            {
                player.lives--;
                tonePlayerHit();
                
                asteroid.deactivate();
                break;
            }

            FOREACH_ACTIVE(bullet, bullets, true)
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

                        score += L_POINTS;
                    }
                    else
                    {
                        score += S_POINTS;
                    }

                    toneAsteroidHit();

                    asteroid.deactivate();
                    bullet.deactivate();

                    break; //exit the loop for this iteration since the bullet is no longer valid, so dont check any other asteroids
                }
            }
        }

        tickLED(player.lives);


        player.render(display);

        FOREACH_ACTIVE(bullet, bullets, true)
            bullet.render(display);

        FOREACH_ACTIVE(asteroid, asteroids, true)
            asteroid.render(display);

        display.display();
    }
}