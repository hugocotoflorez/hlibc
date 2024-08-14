#include "string.h"

int
strcmp(const char *s1, const char *s2)
{
    return memcmp(s1, s2, strlen(s1));
}
