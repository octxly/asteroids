#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "Screendim.h"
#include "Asteroid/Asteroid.h"
#include "Bullet/Bullet.h"
#include "Player/Player.h"

#define ULONG_MAX 4294967295UL

#define OLED_RESET -1 //idk but im supposed to do this
Adafruit_SSD1306 display(SCREEN_WIDTH_ACTUAL, SCREEN_HEIGHT_ACTUAL, &Wire, OLED_RESET);

// List<Asteroid, 12> asteroids;

Player player;

auto asteroid = Asteroid(
    Vector2<int16_t>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
    Vector2<int8_t>(0, 0),
    0
);

Bullet bullets[5];

unsigned long lastAstSpawn = 0;
unsigned long lastHit = 0;

uint16_t score = 0;
bool hasStarted = false;

// auto ledControl = LEDControl(10);

//delta time stuff
unsigned long timer = 0;
unsigned long delta = 0;

void setup() {
    //resetting the board (just in case)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(1);
    display.setTextSize(1);

    randomSeed(analogRead(A6));

    // avRam = availableMemory();
}

void loop() {
    unsigned long now = millis();
    delta = now - timer;

    if (delta >= 16)
    {
        timer = now;

        display.clearDisplay();

        player.update();
        asteroid.update();

        for (auto& bullet : bullets)
        {
            if (bullet.isActive())
            {
                bullet.update();
            }
        }

        player.render(display);
        asteroid.render(display);

        

        display.display();
    }
}