#ifndef BULLETMANAGER
#define BULLETMANAGER

#include <Adafruit_SSD1306.h>
#include "Bullet.cpp"
#include "ArrayList.cpp"

class BulletManager{
    private:
        Adafruit_SSD1306 *display;

    public:
        ArrayList<Bullet, 10> bullets;

        BulletManager(Adafruit_SSD1306 *display) : display(display) {}

        void update(float deltaTime){
            bullets.forEach([this, deltaTime](Bullet *element){
                element->pos.x += element->dir.x * element->speed * deltaTime;
                element->pos.y += element->dir.y * element->speed * deltaTime;

                if (element->markedDelete || element->pos.x >= SCREEN_WIDTH || element->pos.x < 0 || element->pos.y >= SCREEN_HEIGHT || element->pos.y < 0)
                    bullets.remove(element);
            });
        }

        void render(){
            bullets.forEach([this](Bullet *element){
                display->drawPixel(element->pos.x, element->pos.y, 1);
            });
        }
};

#endif