/*
 * File: generators.c
 */
#include <stdlib.h>
#include <stdio.h>

#include "maps.h"
#include "generator.h"
#include "time.h"

/* 
 * Create the statically defined global arrays 
 *  
 *  NOTE: the order here is important. There order in which a value is defined 
 *        must correspond to the value of constant index defined in maps.h
 *
 */

// Create the MAP_FUNCTION_TABLE
map_function MAP_FUNCTION_TABLE[MAP_COUNT] = {
  MAP_CONTROL,
  MAP_CHEBYSHEV,
  MAP_CIRCLE,
  MAP_GAUSS, 
  MAP_ITERATIVE,
  MAP_LOGISTIC,
  MAP_MTENT,
  MAP_PIECEWISE,
  MAP_SINE,
  MAP_SINGER,
  MAP_SINUSOIDAL
};

char *MAP_TAG_TABLE[MAP_COUNT] = {
  "control",
  "chebyshev",
  "circle",
  "gauss",
  "iterative",
  "logistic",
  "mtent",
  "piecewise",
  "sine",
  "singer",
  "sinusoidal"
};

/*
 * create_generator - creates a new instance of a PRNG_t structure
 *                    and seeds it with the initial x-value provided.
 *
 *  WARNINGS:
 *    - Providing an x_0 not in the proper bounds will cause the RNG
 *        to fail.
 *
 *  EXTENSIBILITY:
 *    - This must be carefully modified when introducing a new map to
 *        the program if said map requires special consideration with
 *        seeding and/or non-standard bounds.
 *
 *  ALLOCATES:
 *    - A PRNG_t which is returned. It's the caller's responsibility to
 *        free this.
 */
PRNG_t *create_generator(int id, double x_0) {
  PRNG_t *prng = (PRNG_t *) malloc( sizeof(PRNG_t) );
  if (prng == NULL) {
    printf("BAD BAD NOT GOOD MALOC IN create_generator\n");
    return NULL;
  }
  // ToDo: MALLOC CHECK
    
  prng->map_id = id;


  /*
   * Set the bounds.
   * Special Cases:
   *  - Iterative map on [-1, 1]
   *  - Sinusoidal map on [0.5, 1]
   */
  if (prng->map_id == ITERATIVE) {
    prng->bound_type = BOUNDS_ABNORMAL;
    prng->lbound = ITERATIVE_LBOUND;
    prng->ubound = ITERATIVE_UBOUND;
  
  } else if (prng->map_id == SINUSOIDAL) {
    prng->bound_type = BOUNDS_ABNORMAL;
    prng->lbound = SINUSOIDAL_LBOUND;
    prng->ubound = SINUSOIDAL_UBOUND;
  } else { 
    // Default case: the map's bounds match the range [0,1]
    prng->bound_type = BOUNDS_NORMAL;
    prng->lbound = GEN_LBOUND;
    prng->ubound = GEN_UBOUND;
  }

  // Set the initial value
  // ToDo: Bounds check this?
  if (prng->map_id == CONTROL) {
    // Special Case: Control PRNG
    srand(time(NULL));
    prng->x_n = 0;
  } else if (prng->map_id == SINUSOIDAL) {
    // Special Case: Sinusoidal PRNG
    //    Lower bound on map requires the seed be greater than 1/2.
    while (x_0 < 0.5)
      x_0 *= 2.0;
      prng->x_n = x_0;
  } else {
    // Default Case
      prng->x_n = x_0;
  }

  return prng;
}
