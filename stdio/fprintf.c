#include "stdio.h"
#include "stddef.h"

int printf(const char *format, ...)
{
    fprintf(stdin, const char *format, ...)
}

int fprintf(FILE *stream, const char *format, ...);
int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char str, size_t size, const char *format, ...);
