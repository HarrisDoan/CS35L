#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rand64-sw.h"

FILE *urandstream;
bool mrand;
struct drand48_data buf;

void software_rand64_init(char *filename, bool mrand48_r) {
    mrand = mrand48_r;

    if (mrand) {
        //Generates random numbers in a uniform distribution
        srand48_r(time(NULL), &buf);
    } else {
        //file not specified, use /dev/random
        if (filename[0] == '\0') {
            strcpy(filename, "/dev/random");
        }
        //filename specified, our input
        urandstream = fopen(filename, "r");
        if (!urandstream) {
            abort();
        }
    }
}

unsigned long long software_rand64(void) {
    unsigned long long int x;

    if (mrand) {
        long lower32;
        long upper32;
        mrand48_r(&buf, &lower32);
        mrand48_r(&buf, &upper32);
        x = (upper32 << 32 | lower32);
    }

    else {
        if (fread(&x, sizeof x, 1, urandstream) != 1) abort();
    }
    return x;
}

void software_rand64_fini(void) {
    if (!mrand) {
        fclose(urandstream);
    }
}