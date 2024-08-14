#include "string.h"

char *
strncpy(char *dest, const char *src, size_t n)
{
    return memcpy(dest, src, n);
}
