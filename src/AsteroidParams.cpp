#ifndef ASTEROIDPARAMS
#define ASTEROIDPARAMS

class Params{
    public:
        int numVertex;
        int radius;
        float minMag;
        float maxMag;
    
        Params(int numVertex, int radius, float minMag, float maxMag) :
            numVertex(numVertex), radius(radius), minMag(minMag), maxMag(maxMag) {}
};

#endif