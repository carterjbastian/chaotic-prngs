/*
 * File - utils.c
 *
 * ToDo:
 *  - Malloc Checking
 *  - IO function checking
 *  - Return value checking
 *
 */
#include <stdlib.h>                       // malloc(), free()
#include <limits.h>                       // UINT_MAX
#include <string.h>                       // strlen(), strcat()
#include <stdio.h>                        // FILE, fopen(), fprintf(),


#include "generator.h"
#include "utils.h"                        // public prototypes, formatting constants

double uint_to_double(unsigned int big_int) {
  return (double) big_int / UINT_MAX;
}

unsigned int double_to_uint(double decimal) {
  return decimal * UINT_MAX;
}

double normalize(double x, double lbound, double ubound) {
  return (((x - lbound) * (GEN_UBOUND - GEN_LBOUND)) / (ubound - lbound));
}

/*
 * ALLOCATES: a char * which is returned. It is the caller's responsibility to
 *      free this string.
 */
char *concatenate_fname(const char *path, const char *base, const char *ext) {
  int path_len = strlen(path);
  int base_len = strlen(base);
  int ext_len = strlen(ext);
  int char_count = path_len + base_len + ext_len;
  
  // Allocate the string for the filename
  char *fname = (char *) malloc((char_count + 1) * sizeof(char));
  memset((void *)fname, 0, char_count + 1);
  if (fname == NULL) {
    printf("Failed to Allocate\n");
    return NULL;
  }

  // Concatenate the constant literals into the dynamically allocated string
  sprintf(fname, "%s%s%s", path, base, ext);
  //strcat(fname, path);
  //strcat(fname, base);
  //strcat(fname, ext);
  return fname;
}

void write_header(FILE *f_out, const char *rng_name, unsigned int seed, int count) {
  fprintf(f_out, "%s\n", H_DIV);
  fprintf(f_out, "# generator %s  seed %u\n", rng_name, seed);
  fprintf(f_out, "%s\n", H_DIV);
  fprintf(f_out, "type: %s\n", H_TYPE);
  fprintf(f_out, "count: %d\n", count);
  fprintf(f_out, "numbit: %d\n", H_NUMBIT);
}

FILE *generate_output_file(const char *rng_name, unsigned int seed, int count) {
  char *fname = concatenate_fname(OUTPUT_PATH, rng_name, OUTPUT_EXT);
  // ToDo: Check Retval
  FILE *f_out = fopen(fname, "w");
  write_header(f_out, rng_name, seed, count);
  free(fname);
  return f_out;
}

FILE *generate_trace_file(const char *rng_name) {
  char *fname = concatenate_fname(TRACE_PATH, rng_name, TRACE_EXT);
  // ToDo: Check retval
  FILE *f_out = fopen(fname, "w");
  free(fname);
  return f_out;
}
