#ifndef RAND64_SW_H
#define RAND64_SW_H
#include <stdbool.h>
#include <stdio.h>

void software_rand64_init(char *filename, bool mrand48_r);

unsigned long long software_rand64(void);

void software_rand64_fini(void);

#endif