
#include "Trig.h"

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

int8_t fastCosine(uint8_t angle)
{
    return fastSine(64 + angle);
}