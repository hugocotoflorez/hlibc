#include "string.h"

size_t
strnlen(const char *s, size_t n)
{
    size_t size = 0;

    while (*s && n--)
    {
        ++size;
        ++s;
    }

    return size;
}
