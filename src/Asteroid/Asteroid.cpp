#include "Asteroid.h"
#include "Screendim.h"

//sine lookup of first quarter of the function, split into 32 parts, from 0-32
constexpr int8_t sinLUT[32] = {0,2,3,5,6,8,9,11,12,14,15,16,18,19,20,21,23,24,25,26,27,27,28,29,30,30,31,31,31,32,32,32,};

int8_t fastSine(uint8_t angle)
{
    //Modulo 64, divide by 2 for range of 32
    uint8_t index = (angle & 63) >> 1;

    if (angle < 64)
    {
        return sinLUT[index];
    }

    if (angle < 128)
    {
        return sinLUT[31 - index];
    }

    if (angle < 192)
    {
        return -sinLUT[index];
    }

    return -sinLUT[31 - index];
}
inline int8_t fastCosine(uint8_t angle)
{
    return fastSine(64 + angle);
}


void Asteroid::calcMags()
{
    for (uint8_t i = 0; i < (stage ? S_N_VERTEX : L_N_VERTEX); i++){
        vertexMagnitudes[i] = random(stage ? S_MIN_MAG : L_MIN_MAG, stage ? S_MAX_MAG : L_MAX_MAG);
    }

    rotationSpeed = random(SPIN_MAX + 1);
    rotationSpeed *= random(2) == 0 ? 1 : -1; //Randomize spin direction;
}

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

    Vector2<int16_t> prev = Vector2<int16_t>(
        (fastCosine(currentAngle - angleStep) * vertexMagnitudes[nVert - 1]) >> 2,
        (fastSine(currentAngle - angleStep) * vertexMagnitudes[nVert - 1]) >> 2
    );

    for (int i = 0; i < nVert; i++)
    {
        Vector2<int16_t> curr = Vector2<int16_t>((fastCosine(currentAngle) * vertexMagnitudes[i]) >> 2, (fastSine(currentAngle) * vertexMagnitudes[i]) >> 2);

        display.drawLine(scaleDown(position.x + prev.x), scaleDown(position.y + prev.y), scaleDown(position.x + curr.x), scaleDown(position.y + curr.y), WHITE);

        currentAngle += angleStep;
        prev = curr;
    }
}