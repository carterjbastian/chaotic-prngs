#ifndef _MAPS_H_
#define _MAPS_H_
/*
 * maps.h
 *
 */


/* Indices into the MAP_FUNCTION_TABLE and MAP_INDEX_TABLE */
#define CONTROL     0
#define CHEBYSHEV   1
#define CIRCLE      2
#define GAUSS       3
#define ITERATIVE   4
#define LOGISTIC    5
#define MTENT       6
#define PIECEWISE   7
#define SINE        8
#define SINGER      9
#define SINUSOIDAL  10

// Abnormal bounds
#define ITERATIVE_LBOUND  -1.0
#define ITERATIVE_UBOUND  1.0
#define SINUSOIDAL_LBOUND 0.5
#define SINUSOIDAL_UBOUND 1.0


// All of the constant values needed to iterate the maps
#define CHEBYSHEV_M 0.5
#define CIRCLE_A  0.5
#define CIRCLE_B  0.2
#define GAUSS_A   8.0
#define GAUSS_B   -0.6
#define ITERATIVE_A 0.7
#define LOGISTIC_R  3.57
#define MTENT_U    0.7
#define MTENT_V    (10.0 / 3.0)
#define PIECEWISE_P    0.4
#define PIECEWISE_Q    0.5
#define SINGER_U  1.07
#define SINGER_A  -13.302875
#define SINGER_B  28.75
#define SINGER_C  -23.31
#define SINGER_D  7.68
#define SINUSOIDAL_A  2.3


// Declaration of all of the map functions
double MAP_CONTROL(double x_n, int iteration);
double MAP_CHEBYSHEV(double x_n, int iteration);
double MAP_CIRCLE(double x_n, int iteration);
double MAP_GAUSS (double x_n, int iteration);
double MAP_ITERATIVE(double x_n, int iteration);
double MAP_LOGISTIC(double x_n, int iteration);
double MAP_MTENT(double x_n, int iteration);
double MAP_PIECEWISE(double x_n, int iteration);
double MAP_SINE(double x_n, int iteration);
double MAP_SINGER(double x_n, int iteration);
double MAP_SINUSOIDAL(double x_n, int iteration);

#endif // _MAPS_H_
