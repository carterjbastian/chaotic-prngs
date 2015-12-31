#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define COUNT 10000000
#define NUMBIT 32

#define SUCCESS 0
#define FAILURE 1

#define SINUSOIDAL_A  2.3

char *hdiv = "#==================================================================";
char *fname = "sinusoidal_output.txt";
char *type = "d";

double iterate(double x_n) {
  return (SINUSOIDAL_A * x_n * x_n * sin(M_PI * x_n));
}

unsigned int double_to_uint(double decimal) {
  return decimal * UINT_MAX;
}

double uint_to_double(unsigned int big_int) {
  return (double) big_int / UINT_MAX;
}

double normalize_output(double x) {
  double raw_lbound = 0.5;
  double raw_ubound = 1.0;
  double norm_lbound = 0.0;
  double norm_ubound = 1.0;
  return (((x - raw_lbound) * (norm_ubound - norm_lbound)) / (raw_ubound - raw_lbound));
}

void write_header(FILE *f_out, char *rng_name, unsigned int seed, char *type) {
  fprintf(f_out, "%s\n", hdiv);
  fprintf(f_out, "# generator %s  seed %u\n", rng_name, seed);
  fprintf(f_out, "%s\n", hdiv);
  fprintf(f_out, "type: %s\n", type);
  fprintf(f_out, "count: %d\n", COUNT);
  fprintf(f_out, "numbit: %d\n", NUMBIT);
}

FILE *generate_output_file(char *fname, char *rng_name, unsigned int seed, char *type) {
  FILE *f_out = fopen(fname, "w");
  write_header(f_out, rng_name, seed, type);
  return f_out;
}

int main() {
  /* local variables */
  double x_n;             // The value of latest map iteration in range [0,1]
  unsigned int seed;      // The seed value of the map

  // Set up the seed with the built in modules
  seed = time(NULL);
  FILE *f_out = generate_output_file(fname, "sinusoidal", seed, type);
  x_n = uint_to_double(seed);
  if (x_n < 0.5) {
    x_n *= 2;
    seed = double_to_uint(x_n);
  }

  //x_n = 0.6;

  for (int i = 0; i < COUNT; i++) {
    x_n = iterate(x_n);
    fprintf(f_out, "%u\n", double_to_uint(normalize_output(x_n)));
  }
} 
