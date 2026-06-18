#ifndef ASTEROIDPARAMS
#define ASTEROIDPARAMS

#define AST_SPAWNRATE 1000 //milliseconds
#define SPIN_MAX 3 //Asteroid spin speed max. deg/s.
#define BORDER_BUFFER 80

#define ASTEROID_NUM_SPLIT_MIN 2
#define ASTEROID_NUM_SPLIT_MAX 4

#define ASTEROID_LARGE 0
#define ASTEROID_SMALL 1

#define FORWARD_SPREAD 4 //Forward direction spread on spawn velocity
#define SIDE_SPREAD 3 //Side direction spread on spawn velocity
#define VELOCITY_DIFF 1 //Change in velocity x and y after break apart
#define POSITION_DIFF 40 //Change in position after break apart

#define L_N_VERTEX 8
#define L_MIN_MAG 5
#define L_MAX_MAG 15
#define L_SP_FREQ 3 //Large and small spawn frequencies are ratios!
#define L_POINTS 2

#define S_N_VERTEX 6
#define S_MIN_MAG 2
#define S_MAX_MAG 8
#define S_SP_FREQ 2
#define S_POINTS 3

#endif