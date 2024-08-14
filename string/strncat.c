#include "string.h"

char *
strncat(char *dest, const char *src, size_t n)
{
    void *ret = dest;

    while (*dest)
        ++dest; // move dest to '\0'

    while (*src && n--)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    return ret;
}
