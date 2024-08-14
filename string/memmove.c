#include "../assert/assert.h"
#include "../malloc/malloc.h"
#include "string.h"

void *
memmove(void *dest, const void *src, size_t n)
{
    void *temp = malloc(n + 1);
    assert(temp != NULL);

    memcpy(temp, src, n);
    memcpy(dest, temp, n);
    free(temp);

    return dest;
}
