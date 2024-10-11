#include "string.h"

char *
strtok(char *s, const char *delim)
{
    while (*s)
    {
        if (!strcmp(s, delim))
        {
            *s = '\0';
            return ++s;
        }
    }
    return NULL;
}
