#include "string.h"

static char *__strtok_next;

/* Very important message!!!!
 * This funcion dont work.
 * I think it does but as I
 * didnt test it I assume it
 * dont work as it should */
char *
strtok(char *s, const char *delim)
{
    char *start;

    if (s == NULL)
        s = __strtok_next;

    while (*s && strcmp(s, delim))
        ++s;

    *s = 0;
    s += strlen(delim);
    __strtok_next = s;

    return start;
}
