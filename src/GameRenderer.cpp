#ifndef GAMERENDERER
#define GAMERENDERER

#include "Player.cpp"
#include "Bullet.cpp"
#include "ArrayList.cpp"

class GameRenderer{
  private:
    Player *player;

  public:
    void setPlayer(Player *plr){ player = plr; }

    void addBullet(Bullet bullet){
      player->bullets.add(bullet);
    }

    void update(float deltaTime){
      player->update(deltaTime);
      
      player->bullets.forEach([this, deltaTime](Bullet *element){
        if (!element->markedDelete){
          element->update(deltaTime);
          element->render();

          
        } else {
          player->bullets.remove(element);
        }
      });
      
      player->render();
    }
};

#endif
