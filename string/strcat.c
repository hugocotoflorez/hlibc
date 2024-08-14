#include "string.h"

char *
strcat(char *dest, const char *src)
{
    void *ret = dest;

    while (*dest)
        ++dest; // move dest to '\0'

    while (*src)
    {
        *dest = *src;
        ++dest;
        ++src;
    }

    return ret;
}
