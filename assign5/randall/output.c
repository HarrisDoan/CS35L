#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "output.h"


bool write_bytes(unsigned long long x, int nbytes) {
    do {
        if (putchar(x) < 0) return false;
        x >>= CHAR_BIT;
        nbytes--;
    } while (0 < nbytes);

    return true;
}

void gen_word(unsigned long long x, char *word) {
    for (int i = 7; i >= 0; i--) {
        word[i] = (char)(x & 0xff);
        x >>= 8;
    }
}

void group(char *buf, int nbytes, int N) {
    int remaining_bytes = nbytes;
    char *current_group = buf;
    while (remaining_bytes > 0) {
        int group_size = (remaining_bytes < N) ? remaining_bytes : N;
        write(1, current_group, group_size);
        current_group += group_size;
        remaining_bytes -= group_size;
    }
}