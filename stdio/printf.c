#include "stddef.h"
#include "stdio.h"

#define printf(format, ...)                    \
    {                                          \
        fprintf(stdin, format, ##__VA_ARGS__); \
    }

int
fprintf(FILE *stream, const char *format, ...)
{

}

int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char str, size_t size, const char *format, ...);
