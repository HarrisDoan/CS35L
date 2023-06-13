#ifndef OUTPUT_H
#define OUTPUT_H
#include <stdbool.h>

bool write_bytes(unsigned long long x, int nbytes);
void gen_word(unsigned long long x, char *word);
void group(char *buf, int nbytes, int N);

#endif