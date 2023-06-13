#include "options.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_options(int argc, char **argv, bool *rdrand, bool *mrand48_r, long long *num_bytes, char *filename, int *N, bool *doGroup) 
{
    *num_bytes = 0;
    *rdrand = false;
    *mrand48_r = false;
    strcpy(filename, "");
    *N = 0;
    *doGroup = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (++i < argc) {
                if (strcmp(argv[i], "rdrand") == 0) {
                    *rdrand = true;
                } else if (strcmp(argv[i], "mrand48_r") == 0) {
                    *mrand48_r = true;
                } else if (argv[i][0] == '/') {
                    strcpy(filename, argv[i]);
                } else {
                    fprintf(stderr, "ERROR: -i requires rdrand or mrand48_r or " "/path\n");
                    return 1;
                }
            } else {
                fprintf(stderr, "ERROR: -i option requires an argument\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (++i < argc) {
                if (strcmp(argv[i], "stdio") == 0) {
                    continue;
                } else {
                    *doGroup = true;
                    char *endptr;
                    errno = 0;
                    *N = strtoull(argv[i], &endptr, 10);
                    if (*N < 0) {
                        fprintf(stderr, "ERROR: N must be a non-negative integer\n");
                        return 1;
                    }
                    if (errno || *endptr != '\0') {
                        fprintf(stderr, "ERROR: N is not a valid integer\n");
                        return 1;
                    }
                }
            } else {
                fprintf(stderr, "ERROR: -o option requires an argument\n");
                return 1;
            }
        } else if (*num_bytes == 0) {
            char *endptr;
            errno = 0;
            *num_bytes = strtoll(argv[i], &endptr, 10);
            if (*num_bytes < 0) {
                fprintf(stderr, "ERROR: Number of bytes must be a non-negative integer\n");
                return 1;
            }
            if (errno || *endptr != '\0') {
                fprintf(stderr, "ERROR: Number of bytes is not a valid integer\n");
                return 1;
            }
        } else {
            fprintf(stderr, "ERROR: Unexpected argument: %s\n", argv[i]);
            return 1;
        }
    }

    if (!(*rdrand) && !(*mrand48_r) && filename[0] != '/') {
        *rdrand = true;
    }

    if (*num_bytes == 0) {
        fprintf(stderr, "ERROR: Number of Bytes is not given or incorrect amount was given\n");
        return 1;
    }

    return 0;
}
