#ifndef ASTEROIDPARAMS
#define ASTEROIDPARAMS

struct AsteroidParams{
    int numVertex;
    int radius;
    float minMag;
    float maxMag;

    AsteroidParams(int numVertex, int radius, float minMag, float maxMag) :
        numVertex(numVertex), radius(radius), minMag(minMag), maxMag(maxMag) {}
};

#endif