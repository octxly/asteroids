#ifndef ASTEROIDPARAMS
#define ASTEROIDPARAMS

#define AST_SPAWNRATE 1.5
#define SPLIT_DIFF 60 //After a large asteroid is hit, change in direction in degrees
#define SPIN_MAX 60 //Asteroid spin speed max. deg/s.

#define L_N_VERTEX 8
#define L_RAD 10 //MAX 25.5 RADIUS DUE TO INTEGER OVERFLOW
#define L_MIN_MAG 0.65
#define L_MAX_MAG 1.35
#define L_SPEED 15
#define L_SP_FREQ 3 //Large and small spawn frequencies are ratios!
#define L_POINTS 50

#define S_N_VERTEX 6
#define S_RAD 5
#define S_MIN_MAG 0.65
#define S_MAX_MAG 1.35
#define S_SPEED 25
#define S_SP_FREQ 2
#define S_POINTS 100

#endif