#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Button.cpp"
#include "Joystick.cpp"
#include "Player.cpp"
#include "GameRenderer.cpp"
#include "Bullet.cpp"
#include "ArrayList.cpp"

#define ULONG_MAX 4294967295UL

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Joystick joystick(A6, A7);
Button btn1(2);
Button btn2(3);

GameRenderer gameRenderer;

Player player(&display, Vector2(8, 10), Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, &joystick, &btn1, &btn2);

unsigned long timer = 0;
unsigned long delta = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  
  display.setTextColor(1);
  display.setTextSize(1);

  gameRenderer.setPlayer(&player);
}

void loop() {
  display.clearDisplay();
  joystick.updateJoystick();
  // btn1.updateButton();
  // btn2.updateButton();

  gameRenderer.update(delta);

  display.display();

  do delta = (millis() - timer) % ULONG_MAX;
  while (delta < 1);
  timer = millis();
}
