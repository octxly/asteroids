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

#define magnitude(a1, a2) (sqrt(sq((a1)) + sq((a2))))
#define findLowest(a, b, c) (min(min((a), (b)), (c)))
#define findHighest(a, b, c) (max(max((a), (b)), (c)))

#define ACCEL 45
#define DECEL 30
#define MAXSPD 60

class Player{
    public:
        Vector2<float> pos; //regular. tried fixed-point representation, but it was too off-putting
        Vector2<uint8_t> dim; //dimensions aren't large = +255
        Vector2<float> vel; //regular. tried fixed-point representation, but it was too off-putting
        float rotation;

        Vector2<float> lastJoyPos;

        Joystick joystick = Joystick(A6, A7);
        Button btn1 = Button(2);
        Button btn2 = Button(3);

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

        List<Bullet, 10> bullets;
        
        Player(Vector2<uint8_t> dim, Vector2<float> pos, float rotation) :
            pos(pos), dim(dim), rotation(rotation) {}

        void update(float deltaTime){
            if (joystick.xActuated() || joystick.yActuated()){
                rotation = joystick.readDeg();
                lastJoyPos = joystick.readNormalized();
            }

            float magnitude = magnitude(vel.x, vel.y);
            float decelRate = DECEL * deltaTime;
            float deMag = magnitude - decelRate;

            Vector2<float> joyPos = joystick.readRaw(); //different from lastJoyPos since this runs even if joystick not actuated

            if (joyPos.x != 0 && btn1.getState())
                vel.x += ACCEL * joyPos.x * deltaTime;
            else 
                vel.x *= decelRate >= magnitude ? 0 : deMag / magnitude;

            if (joyPos.y != 0 && btn1.getState())
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

            if (btn2.getState() && !hasFired && bullets.getMax() > bullets.getSize()){
                hasFired = true;

                bullets.add(Bullet(Vector2<uint8_t>(pos.x, pos.y), Vector2<int8_t>(lastJoyPos.x * 100, lastJoyPos.y * 100)));
            } else if (!btn2.getState() && hasFired) hasFired = false;
        }

        void render(Adafruit_SSD1306 *display){
            Vector2<float> top = rotateAround(Vector2<float>(pos.x, pos.y - dim.y / 2));
            Vector2<float> left = rotateAround(Vector2<float>(pos.x + dim.x / 2, pos.y + dim.y / 2));
            Vector2<float> right = rotateAround(Vector2<float>(pos.x - dim.x / 2, pos.y + dim.y / 2));

            display->fillTriangle(
                top.x, top.y,
                left.x, left.y,
                right.x, right.y,
                1
            );

            bool wrapX = findLowest(top.x, left.x, right.x) < 0 || findHighest(top.x, left.x, right.x) >= SCREEN_WIDTH;
            bool wrapY = findLowest(top.y, left.y, right.y) < 0 || findHighest(top.y, left.y, right.y) >= SCREEN_HEIGHT;
   
            if (wrapX || wrapY){
                int16_t xOffset = wrapX ? (findLowest(top.x, left.x, right.x) < 0 ? SCREEN_WIDTH : -SCREEN_WIDTH) : 0;
                int16_t yOffset = wrapY ? (findLowest(top.y, left.y, right.y) < 0 ? SCREEN_HEIGHT : -SCREEN_HEIGHT) : 0;
    
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