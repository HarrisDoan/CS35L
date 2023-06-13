#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdbool.h>

int get_options(int argc, char **argv, bool *rdrand, bool *mrand48_r, long long *num_bytes, char *filename, int *N, bool *doGroup);

#endif
