#include "../include/common_funcs.h"
#include <string.h>

int read_phrase(char* string, FILE* file)
{
    assert(string);
    assert(file);

    int ch = fgetc(file);
    if (ch != '<') {
        return 1;
    }

    ch = fgetc(file);
    for (int i = 0; i == MAX_STRLEN - 1 || ch != '>'; i++) {
        string[i] = (char) ch;
        ch = fgetc(file);
    }

    return 0;
}

char* get_string(char* string, int max_len)
{
    fgets(string, max_len, stdin);
    *strchr(string, '\n') = '\0';
    return string;
}
