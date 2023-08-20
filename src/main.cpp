#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "Game.cpp"
#include "Screendim.h"

#define ULONG_MAX 4294967295UL

#define OLED_RESET -1 //idk but im supposed to do this
Adafruit_SSD1306 display(SCREEN_WIDTH_FULL, SCREEN_HEIGHT_FULL, &Wire, OLED_RESET);

int availableMemory(); //forward declaration

//game objects
Game game(&display);

//delta time stuff
unsigned long timer = 0;
unsigned long delta = 0;

uint16_t avRam;

void setup() {
    //resetting the board (just in case)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(1);
    display.setTextSize(1);

    randomSeed(analogRead(0));

    avRam = availableMemory();
}

void loop() {
    display.clearDisplay();

    //dev stuff
    // display.setCursor(0, 0);
    // // display.println(String(avRam));
    // display.println(String(1000.0 / delta));

    game.update(delta / 1000.0); //Game loop.

    display.display();

    //i honestly don't know. a friend gave me this code
    do delta = (millis() - timer) % ULONG_MAX;
    while(delta < 1);

    timer = millis();
}

int availableMemory() {
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL);
    free(buf);
    return size;
}