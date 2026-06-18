#include "Asteroid.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Screendim.h"
#include "Math/Trig.h"

void Asteroid::calcMags()
{
    uint16_t sum = 0;

    for (uint8_t i = 0; i < (stage ? S_N_VERTEX : L_N_VERTEX); i++){
        vertexMagnitudes[i] = random(stage ? S_MIN_MAG : L_MIN_MAG, stage ? S_MAX_MAG : L_MAX_MAG);
        sum += vertexMagnitudes[i];
    }

    averageMagnitude = sum / (stage? S_N_VERTEX : L_N_VERTEX);

    rotationSpeed = random(SPIN_MAX + 1);
    rotationSpeed *= random(2) == 0 ? 1 : -1; //Randomize spin direction;
}

Asteroid::Asteroid() = default;

Asteroid::Asteroid(Vector2<int16_t> position, Vector2<int8_t> direction, uint8_t stage) :
position(position), velocity(direction), stage(stage), rotation(0)
{
    calcMags();
}

void Asteroid::update()
{
    position.x += velocity.x;
    position.y += velocity.y;

    rotation += rotationSpeed;
}

void Asteroid::render(Adafruit_SSD1306& display) const
{
    //rotation is 0-255, with naturally occuring reset to 0
    uint8_t currentAngle = rotation;

    uint8_t nVert = stage ? S_N_VERTEX : L_N_VERTEX;

    uint8_t angleStep = 256 / nVert;

    //Start with last vertex and use it
    //trig goes up to 32 while screen scale is at 8, so divide by 4 to compensate
    Vector2<int16_t> prev = Vector2<int16_t>(
        (fastCosine(currentAngle - angleStep) * vertexMagnitudes[nVert - 1]) >> 2,
        (fastSine(currentAngle - angleStep) * vertexMagnitudes[nVert - 1]) >> 2
    );

    for (int i = 0; i < nVert; i++)
    {
        Vector2<int16_t> curr = Vector2<int16_t>((fastCosine(currentAngle) * vertexMagnitudes[i]) >> 2, (fastSine(currentAngle) * vertexMagnitudes[i]) >> 2);

        display.drawLine(SCALE_DOWN(position.x + prev.x), SCALE_DOWN(position.y + prev.y), SCALE_DOWN(position.x + curr.x), SCALE_DOWN(position.y + curr.y), WHITE);

        currentAngle += angleStep;
        prev = curr;
    }
}

Asteroid Asteroid::spawnAsteroid()
{
    uint8_t side = random(4);

    Vector2<int16_t> position;
    Vector2<int8_t> direction;

    if (side == 0) //bottom
    {
        position = Vector2<int16_t>(random(SCREEN_WIDTH), SCREEN_HEIGHT + BORDER_BUFFER);
        direction = Vector2<int8_t>(random(-SIDE_SPREAD, SIDE_SPREAD + 1), random(-FORWARD_SPREAD, 0));
    }
    else if (side == 1) //top
    {
        position = Vector2<int16_t>(random(SCREEN_WIDTH), -BORDER_BUFFER);
        direction = Vector2<int8_t>(random(-SIDE_SPREAD, SIDE_SPREAD + 1), random(1, FORWARD_SPREAD + 1));
    }
    else if (side == 2) //left
    {
        position = Vector2<int16_t>(-BORDER_BUFFER, random(SCREEN_HEIGHT));
        direction = Vector2<int8_t>(random(1, FORWARD_SPREAD), random(-SIDE_SPREAD, SIDE_SPREAD + 1));
    }
    else //right
    {
        position = Vector2<int16_t>(SCREEN_WIDTH + BORDER_BUFFER, random(SCREEN_HEIGHT));
        direction = Vector2<int8_t>(random(-FORWARD_SPREAD, 0), random(-SIDE_SPREAD, SIDE_SPREAD + 1));
    }

    return Asteroid(position, direction, random(2) == 0 ? ASTEROID_LARGE : ASTEROID_SMALL);
}

Asteroid Asteroid::spawnBrokenChunk() const
{
    Vector2<int16_t> pos = Vector2<int16_t>(position.x + random(-POSITION_DIFF, POSITION_DIFF + 1), position.y + random(-POSITION_DIFF, POSITION_DIFF + 1));
    Vector2<int8_t> vel = Vector2<int8_t>(velocity.x + random(-VELOCITY_DIFF, VELOCITY_DIFF + 1), velocity.y + random(-VELOCITY_DIFF, VELOCITY_DIFF + 1));

    return {pos, vel, ASTEROID_SMALL};
}
