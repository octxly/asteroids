#ifndef GAMERENDERER
#define GAMERENDERER

#include <Adafruit_SSD1306.h>
#include "Player.cpp"
#include "Bullet.cpp"
#include "ArrayList.cpp"
#include "Asteroid.cpp"

class GameRenderer{
  private:
    Adafruit_SSD1306 *display;

    Player *player;
 
    ArrayList<Asteroid, 10> asteroids;

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
      
      player->bullets.forEach([this, deltaTime](Bullet *element){
        if (!element->markedDelete){
          element->update(deltaTime);
          element->render();
        }else 
          player->bullets.remove(element);
      });


      // asteroids.forEach([this, deltaTime](Asteroid *element){
      //   if (!element->markedDelete){
      //     element->update(deltaTime);
      //     element->render();
      //   }else
      //     asteroids.remove(element);
      // });
      
      player->render();
    }

    // void addAsteroid(Asteroid asteroid){ asteroids.add(asteroid); }
};

#endif
