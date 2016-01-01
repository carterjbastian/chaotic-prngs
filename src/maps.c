/*
 * File: maps.c
 *
 */

#include <math.h>
#include <stdlib.h>                 // rand()

#include "utils.h"
#include "maps.h"

/* Function definitions for all of the map functions */
double MAP_CONTROL(double x_n, int iteration) {
  unsigned int next = 2 * rand();
  if (rand() % 2 == 0)
    next++;
  return uint_to_double(next);
}

double MAP_CHEBYSHEV(double x_n, int iteration) {
  return ((cos(iteration * (acos(x_n)))) * CHEBYSHEV_M);
}

double MAP_CIRCLE(double x_n, int iteration) {
  return (fmod(x_n + CIRCLE_B - (CIRCLE_A / (2.0 * M_PI)) * (sin(2.0 * M_PI * x_n)), 1.0));
}

double MAP_GAUSS (double x_n, int iteration) {
  return (exp(-1.0 * GAUSS_A * x_n * x_n) + GAUSS_B);
}
double MAP_ITERATIVE(double x_n, int iteration) {
  return (sin((ITERATIVE_A * M_PI) / x_n));
}

double MAP_LOGISTIC(double x_n, int iteration) {
  return ((LOGISTIC_R) * (x_n) * (1.0 - x_n));
}

double MAP_MTENT(double x_n, int iteration) {
  if (x_n < MTENT_U)
    return (x_n / MTENT_U);
  else
    return (MTENT_V * (1.0 - x_n));
}

double MAP_PIECEWISE(double x_n, int iteration) {
  if (x_n >= (1.0 - PIECEWISE_P) && x_n < 1.0) {
    return ((1.0 - x_n) / PIECEWISE_P);
  } else if (x_n >= PIECEWISE_Q && x_n < 1.0 - PIECEWISE_P) {
    return ((1.0 - PIECEWISE_P - x_n) / (PIECEWISE_Q - PIECEWISE_P));
  } else if (x_n >= PIECEWISE_P && x_n < PIECEWISE_Q) {
    return ((x_n - PIECEWISE_P) / (PIECEWISE_Q - PIECEWISE_P));
  } else {
    return (x_n / PIECEWISE_P);
  }
}

double MAP_SINE(double x_n, int iteration) {
  return (sin(M_PI * x_n));
}

double MAP_SINGER(double x_n, int iteration) {
  double res = (SINGER_U * 
      (SINGER_A * pow(x_n, 4) +
       SINGER_B * pow(x_n, 3) +
       SINGER_C * pow(x_n, 2) +
       SINGER_D * x_n));
  return res;
}

double MAP_SINUSOIDAL(double x_n, int iteration) {
  return (SINUSOIDAL_A * x_n * x_n * sin(M_PI * x_n));
}
