#ifndef PLAYER
#define PLAYER

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Vector/Vector2.cpp"
#include "Input/Joystick.cpp"
#include "Input/Button.cpp"
#include "Player/Bullet.cpp"
#include "List.cpp"
#include "Screendim.h"
#include "Ouput/Button.h"

#define magnitude(a1, a2) (sqrt(sq((a1)) + sq((a2))))
#define findLowest(a, b, c) (min(min((a), (b)), (c)))
#define findHighest(a, b, c) (max(max((a), (b)), (c)))

#define ACCEL 60
#define DECEL 30
#define MAXSPD 45
#define FIRERATE 500
#define GRACEPERIOD 3500 //milliseconds

class Player{
    public:
        Vector2<float> pos; //regular. tried fixed-point representation, but it was too off-putting
        Vector2<uint8_t> dim; //dimensions aren't large = +255
        Vector2<float> vel; //regular. tried fixed-point representation, but it was too off-putting
        float rotation = 0;
        unsigned long lastFired = 0;

        Vector2<float> lastJoyPos = Vector2<float>(0, -1);

        Joystick joystick = Joystick(A6, A7);

        Vector2<float> rotateAround(Vector2<float> point){
            float angleRad = radians(rotation);

            float angleCos = cos(angleRad);
            float angleSin = sin(angleRad);
            
            float transX = point.x - pos.x;
            float transY = point.y - pos.y;
            
            return Vector2<float>(
                transX * angleCos - transY * angleSin + pos.x, 
                transX * angleSin + transY * angleCos + pos.y
            );
        }

        List<Bullet, 4> bullets; 
        
        Player(Vector2<uint8_t> dim, Vector2<float> pos) :
            pos(pos), dim(dim) {}

        void update(float deltaTime){
            if (joystick.xActuated() || joystick.yActuated()){
                rotation = joystick.readDeg();
                lastJoyPos = joystick.readNormalized();
            }

            float magnitude = magnitude(vel.x, vel.y);
            float decelRate = DECEL * deltaTime;
            float deMag = magnitude - decelRate;

            Vector2<float> joyPos = joystick.readRaw(); //different from lastJoyPos since this runs even if joystick not actuated

            if (joyPos.x != 0 && digitalRead(BTN1))
                vel.x += ACCEL * joyPos.x * deltaTime;
            else 
                vel.x *= decelRate >= magnitude ? 0 : deMag / magnitude;

            if (joyPos.y != 0 && digitalRead(BTN1))
                vel.y += ACCEL * joyPos.y * deltaTime;
            else 
                vel.y *= decelRate >= magnitude ? 0 : deMag / magnitude;

            //This kinda sucks and is slow, but I'm yet to find a workaround.
            // magnitude = magnitude(vel.x, vel.y); //This could potentially be removed 
            if (magnitude > MAXSPD){
                vel.x *= MAXSPD / magnitude;
                vel.y *= MAXSPD / magnitude;
            }

            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;

            //REVISE THESE
            pos.x -= pos.x > SCREEN_WIDTH ? SCREEN_WIDTH : 0;
            pos.x += pos.x < 0 ? SCREEN_WIDTH : 0;
            
            pos.y -= pos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : 0;
            pos.y += pos.y < 0 ? SCREEN_HEIGHT : 0;

            static bool hasFired = false;

            if (digitalRead(BTN2) && !hasFired && bullets.getMax() > bullets.getSize() && millis() > lastFired + FIRERATE){
                hasFired = true;
                lastFired = millis();

                bullets.add(Bullet(Vector2<uint8_t>(pos.x, pos.y), Vector2<int8_t>(lastJoyPos.x * 100, lastJoyPos.y * 100)));
                
                tone(8, 800, 50);
            } else if (!digitalRead(BTN2) && hasFired) hasFired = false;
        }

        void render(Adafruit_SSD1306 *display, bool inGrace){
            Vector2<float> top = rotateAround(Vector2<float>(pos.x, pos.y - dim.y / 2));
            Vector2<float> left = rotateAround(Vector2<float>(pos.x + dim.x / 2, pos.y + dim.y / 2));
            Vector2<float> right = rotateAround(Vector2<float>(pos.x - dim.x / 2, pos.y + dim.y / 2));

            if (inGrace)
                display->drawTriangle(
                    top.x, top.y,
                    left.x, left.y,
                    right.x, right.y,
                    1
                );
            else 
                display->fillTriangle(
                    top.x, top.y,
                    left.x, left.y,
                    right.x, right.y,
                    1
                );

            float lowestX = findLowest(top.x, left.x, right.x);
            float lowestY = findLowest(top.y, left.y, right.y);

            bool wrapX = lowestX < 0 || findHighest(top.x, left.x, right.x) >= SCREEN_WIDTH;
            bool wrapY = lowestY < 0 || findHighest(top.y, left.y, right.y) >= SCREEN_HEIGHT;
   
            if (wrapX || wrapY){
                int16_t xOffset = wrapX ? (lowestX < 0 ? SCREEN_WIDTH : -SCREEN_WIDTH) : 0;
                int16_t yOffset = wrapY ? (lowestY < 0 ? SCREEN_HEIGHT : -SCREEN_HEIGHT) : 0;
    
                if (inGrace)
                    display->drawTriangle(
                        top.x + xOffset, top.y + yOffset,
                        left.x + xOffset, left.y + yOffset,
                        right.x + xOffset, right.y + yOffset,
                        1
                    );
                else 
                    display->fillTriangle(
                        top.x + xOffset, top.y + yOffset,
                        left.x + xOffset, left.y + yOffset,
                        right.x + xOffset, right.y + yOffset,
                        1
                    );
            }
        }
};

#endif