/*
 * File: run_prng.c
 *
 */

// System includes
#include <stdio.h>                        // fprintf(), fclose()
#include <stdlib.h>                       // free(), atoi()
#include <time.h>                         // time()

// Local includes
#include "utils.h"
#include "generator.h"
#include "maps.h"

#define ITERATE_COUNT   1000000000

extern map_function MAP_FUNCTION_TABLE[MAP_COUNT];
extern char *MAP_TAG_TABLE[MAP_COUNT];
/*
 * main function - runs a chaotic prng and writes results to output file
 *
 * ToDo: 
 *  - Error Printing and Graceful Failing
 *  - Command Line Input
 */
int main(int argc, char *argv[]) {
  /* local variables */
  int map_id;
  unsigned int seed;
  int max_count, i;
  double x_0;
  PRNG_t *prng;
  FILE *f_out = NULL;
  FILE *f_trace = NULL;

  /* Command Line Argument Checking */
  if (argc < 2)
    return -1;

  // ToDo: Error Check!
  map_id = atoi(argv[1]);
  if (map_id >= MAP_COUNT)
    return -1;

  // ToDo: Get the count from command line
  max_count = ITERATE_COUNT;

  /* Set up the seed / initial value for the PRNG */
  seed = time(NULL);
  x_0 = uint_to_double(seed);

  // Set up files for output
  f_out = generate_output_file(MAP_TAG_TABLE[map_id], seed, max_count);
  f_trace = generate_trace_file(MAP_TAG_TABLE[map_id]);
  
  if (f_out == NULL) {
    printf("Failed to make outfile\n");
    return -1;
  }
  if (f_trace == NULL) {
    printf("Failed to make trace file\n");
    return -1;
  }

  /* Set up the chaotic PRNG */
  prng = create_generator(map_id, x_0);

  /* The simulation & output loop */
  for (i = 0; i < max_count; i++) {
    // Get the next number from the generator (perform an iteration of the map)
    prng->x_n = (MAP_FUNCTION_TABLE[map_id]) (prng->x_n, i);

    // Write results to the output and trace files (normalizing if necessary)
    if (prng->bound_type == BOUNDS_ABNORMAL)
      fprintf(f_out, "%u\n", double_to_uint(normalize(prng->x_n, prng->lbound, prng->ubound)));
    else
      fprintf(f_out, "%u\n", double_to_uint(prng->x_n));

    fprintf(f_trace, "%.10f\n", prng->x_n);
  }

  /* Clean up and garbage disposal */
  fclose(f_out);
  fclose(f_trace);
  free(prng);
}
