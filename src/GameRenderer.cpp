#ifndef GAMERENDERER
#define GAMERENDERER

#include <Adafruit_SSD1306.h>
#include "Player.cpp"
#include "ArrayList.cpp"
#include "Asteroid/AsteroidManager.cpp"

class GameRenderer{
  private:
    Adafruit_SSD1306 *display;

    Player *player;
 
    // AsteroidManager asteroidManager = AsteroidManager(display);

    // int asteroidInterval = 15 * 1000;
    // unsigned long lastAsteroidSpawn = 0;

  public:
    GameRenderer(Adafruit_SSD1306 *display) : display(display) {}

    void setPlayer(Player *plr){ player = plr; }

    void update(float deltaTime){
      // if (lastAsteroidSpawn + asteroidInterval < millis()){
      //   asteroids.add(Asteroid(display, Vector2(100, 50), Vector2(0, -1), 0));
      //   lastAsteroidSpawn = millis();
      // }

      player->update(deltaTime);
      player->bulletManager.update(deltaTime);

      // asteroids.forEach([this, deltaTime](Asteroid *element){
      //   if (!element->markedDelete){
      //     element->update(deltaTime);
      //     element->render();
      //   }else
      //     asteroids.remove(element);
      // });
      
      player->render();
      player->bulletManager.render();
    }

    // void addAsteroid(Asteroid asteroid){ asteroids.add(asteroid); }
};

#endif
