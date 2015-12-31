#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define MAX 10000000
int buf_num = sizeof(int) / sizeof(char);

int main() {
  unsigned int *mynum = malloc(sizeof(int));
  unsigned int seed = time(NULL);
  srand(seed); 
  FILE *write_file = fopen("test_out.txt", "w");

  // Set up the header 
  fprintf(write_file, "#==================================================================\n");
  fprintf(write_file, "# generator test  seed = %u\n", seed);
  fprintf(write_file, "#==================================================================\n");
  fprintf(write_file, "type: d\n");
  fprintf(write_file, "count: %d\n", MAX);
  fprintf(write_file, "numbit: %d\n", 32);

  for (int i = 0; i <MAX; i++) {
    *mynum = 2*rand();
    if (rand() % 2 == 0)
      (*mynum)++;

//    memcpy((void *) buf, (void *)mynum, sizeof(int));
    fprintf(write_file, "%u\n", *mynum);
  }
}


