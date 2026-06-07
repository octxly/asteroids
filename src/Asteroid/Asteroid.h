#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "AsteroidParams.h"
#include "Screendim.h"
#include "Vector/Vector2.h"
#include <stdint.h>

class Adafruit_SSD1306;

class Asteroid
{
    Vector2<int16_t> position;
    Vector2<int8_t> velocity;

    uint8_t vertexMagnitudes[L_N_VERTEX];
    uint8_t averageMagnitude;

    uint8_t stage;

    int8_t rotationSpeed;
    uint8_t rotation;

    void calcMags();

public:
    Asteroid();
    Asteroid(Vector2<int16_t> position, Vector2<int8_t> direction, uint8_t stage);

    void update();
    void render(Adafruit_SSD1306& display) const;

    Asteroid spawnBrokenChunk() const;
    
    bool isIntersecting(Vector2<int16_t> point) const
    {
        return Vector2<int32_t>(position.x - point.x, position.y - point.y).lengthSquared() < (averageMagnitude << SCALE_FACTOR)*(averageMagnitude << SCALE_FACTOR);
    }

    bool isOutOfBounds() const
    {
        return position.x < -BORDER_BUFFER || position.x > SCREEN_WIDTH + BORDER_BUFFER || position.y < -BORDER_BUFFER || position.y > SCREEN_HEIGHT + BORDER_BUFFER;
    }

    bool isActive() const
    {
        return velocity.x != 0 || velocity.y != 0;
    }

    void deactivate()
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    uint8_t getStage() const
    {
        return stage;
    }

    static Asteroid spawnAsteroid();
};

#endif //ASTEROIDS_ASTEROID_H
