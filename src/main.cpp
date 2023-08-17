#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "./Input/Button.cpp"
#include "./Input/Joystick.cpp"
#include "Player.cpp"
#include "GameRenderer.cpp"
#include "ArrayList.cpp"

#define ULONG_MAX 4294967295UL

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Joystick joystick(A6, A7);
Button btn1(2);
Button btn2(3);

GameRenderer gameRenderer(&display);

Player player(&display, Vector2S(6, 8), Vector2S(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, &joystick, &btn1, &btn2);

unsigned long timer = 0;
unsigned long delta = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.setTextColor(1);
  display.setTextSize(1);

  gameRenderer.setPlayer(&player);
}
int availableMemory() {
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL);
      free(buf);
    return size;
}
void loop() {
  display.clearDisplay();
  joystick.updateJoystick();

  display.setCursor(0, 0);
  display.println(availableMemory());

  sizeof(Asteroid);

  gameRenderer.update(delta / 1000.0);

  display.display();

  do delta = (millis() - timer) % ULONG_MAX;
  while (delta < 1);
  
  timer = millis();
}

