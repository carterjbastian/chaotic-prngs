#ifndef _UTILS_H_
#define _UTILS_H_
/*
 * File: utils.h
 *
 */

#include <stdio.h>

/* IO and formatting constants */
#define H_DIV       "#=================================================================="
#define H_TYPE      "d"
#define H_NUMBIT    32

#define OUTPUT_PATH "./output/"
#define TRACE_PATH  "./traces/"
#define OUTPUT_EXT  "_out.txt"
#define TRACE_EXT   "_trace.txt"

#define SUCCESS     0x1
#define FAILURE     0x0


/* Public prototypes for utility functions */

double uint_to_double(unsigned int big_int);

unsigned int double_to_uint(double decimal);

double normalize(double x, double lbound, double ubound);

char *concatenate_fname(const char *path, const char *base, const char *ext);

void write_header(FILE *f_out, const char *rng_name, unsigned int seed, int count);

FILE *generate_output_file(const char *rng_name, unsigned int seed, int count);

FILE *generate_trace_file(const char *rng_name);
#endif // _UTILS_H_
