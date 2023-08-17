#ifndef UTILITIES
#define UTILITIES

#include <Arduino.h>
#include "Vector.cpp"

// #define findLowest(a, b, c) (min(min((a), (b)), (c)))
// #define findHighest(a, b, c) (max(max((a), (b)), (c)))
// #define magnitude(a1, a2) (sqrt(sq(a1) + sq(a2)))

Vector2F rotateAround(Vector2S pivot, Vector2S point, float rotation){
    float angleRad = radians(rotation);

    float angleCos = cos(angleRad);
    float angleSin = sin(angleRad);
    
    float transX = point.getX() - pivot.getX();
    float transY = point.getY() - pivot.getY();
    
    float rotatedX = transX * angleCos - transY * angleSin;
    float rotatedY = transX * angleSin + transY * angleCos;
    
    return Vector2F(rotatedX + pivot.getX(), rotatedY + pivot.getY());
}

#endif