#ifndef _GENERATOR_H_
#define _GENERATOR_H_
/*
 * generator.h
 *
 */

/*
 * Includes
 */
#include "maps.h"

/*
 * Constants
 *
 */
#define MAP_COUNT         11
#define GEN_LBOUND        0.0
#define GEN_UBOUND        1.0

#define BOUNDS_NORMAL     0x1
#define BOUNDS_ABNORMAL   0x0

/*
 * Type Definitions for important generator structures
 */
typedef double (*map_function)(double x_n, int iteration);

typedef struct PRNG_t {
  /* Set Up Variables */
  int map_id;                 // The value of the index for this PRNG-type's map

  int bound_type;             // NORMALIZE value indicates if x_values must be 
                              //    normalized to [0,1]
  double lbound;              // Lower bound on the range of raw x_n values
  double ubound;              // Upper bound on the range of raw x_n values

  /* State Variables */
  double x_n;                 // Value of the currently-held one dimensional state
                              //    on [range_lbound, range_ubound]
} PRNG_t; 

/* Declarations of important static globals */
//map_function MAP_FUNCTION_TABLE[MAP_COUNT];
//char * MAP_TAG_TABLE[MAP_COUNT];

/* Public generator prototypes */
PRNG_t *create_generator(int id, double x_0);

#endif // _GENERATOR_H_
