#ifndef GAMERENDERER
#define GAMERENDERER

#include "Player.cpp"
#include "Bullet.cpp"
#include "ArrayList.cpp"
#include "Asteroid.cpp"

class GameRenderer{
  private:
    Player *player;
    // ArrayList<Asteroid, 30> asteroids;

    // int asteroidInterval = 15 * 1000;
    // unsigned long lastAsteroidSpawn = 0;

  public:
    void setPlayer(Player *plr){ player = plr; }

    void update(float deltaTime){
      // if (lastAsteroidSpawn + asteroidInterval < millis()){
      //   asteroids.add(Asteroid(Vector2(), Vector2()));
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
      //   if (!element->markedDelete)
      //     element->update(deltaTime);
      //   else
      //     asteroids.remove(element);
      // });
      
      player->render();
       
    }

    // void addAsteroid(Asteroid asteroid){ asteroids.add(asteroid); }
};

#endif
