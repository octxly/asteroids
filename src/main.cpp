#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Asteroid/Asteroid.h"
#include "Bullet/Bullet.h"
#include "Player/Player.h"

#define ULONG_MAX 4294967295UL

#define NUM_BULLETS 5
#define NUM_ASTEROIDS 20

#define OLED_RESET -1 //idk but im supposed to do this
Adafruit_SSD1306 display(SCREEN_WIDTH_ACTUAL, SCREEN_HEIGHT_ACTUAL, &Wire, OLED_RESET);

Player player;

Bullet bullets[NUM_BULLETS];
Asteroid asteroids[NUM_ASTEROIDS];

unsigned long lastAstSpawn = 0;
unsigned long lastHit = 0;

uint16 score = 0;
bool hasStarted = false;

// auto ledControl = LEDControl(10);

//delta time stuff
unsigned long frameTimer = 0;
unsigned long asteroidTimer = 0;

void spawnAsteroid();
void spawnBullet();

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
        spawnAsteroid();
    }

    if (now - frameTimer >= 16)
    {
        frameTimer = now;

        display.clearDisplay();

        player.update();

        if (player.queueBullet)
        {
            player.queueBullet = false;

            spawnBullet();
        }

        for (auto& bullet : bullets)
        {
            if (bullet.isOutOfBounds())
            {
                bullet.deactivate();
                continue;
            }

            if (bullet.isActive())
            {
                bullet.update();
            }
        }

        for (auto& asteroid: asteroids)
        {
            if (asteroid.isOutOfBounds())
            {
                asteroid.deactivate();
                continue;
            }

            if (asteroid.isActive())
            {
                asteroid.update();
            }
        }


        player.render(display);

        for (auto& bullet : bullets)
        {
            if (bullet.isActive())
            {
                bullet.render(display);
            }
        }

        for (auto& asteroid : asteroids)
        {
            if (asteroid.isActive())
            {
                asteroid.render(display);
            }
        }

        display.display();
    }
}

void spawnAsteroid()
{
    for (int i = 0; i < NUM_ASTEROIDS; i++)
    {
        if (!asteroids[i].isActive())
        {


            break;
        }
    }
}

void spawnBullet()
{
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        if (!bullets[i].isActive())
        {
            bullets[i] = player.generateBullet();

            break;
        }
    }
}