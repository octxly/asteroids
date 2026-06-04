#ifndef SCREENDIM
#define SCREENDIM

//Full dim are the physical dimensions of the screen while regular dim are simulated dim (USED ONLY BY ADAFRUIT SCREEN LIBRARY)
#define SCREEN_WIDTH 1024
#define SCREEN_WIDTH_ACTUAL 128

#define SCREEN_HEIGHT 512
#define SCREEN_HEIGHT_ACTUAL 64

#define SCALE_FACTOR 3 //How much the screen dimensions are "blown up" for simulation

#define scaleDown(x) ((x) >> SCALE_FACTOR)

#endif