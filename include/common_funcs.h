#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H

#include <stdio.h>
#include <assert.h>

const int MAX_STRLEN = 100;

int read_phrase(char* string, FILE* file);
char* get_string(char* string, int max_len);

#endif /* COMMON_FUNCS_H */
