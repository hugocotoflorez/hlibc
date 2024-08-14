#include "../assert/assert.h"
#include "../malloc/malloc.h"
#include "../math/math.h"
#include "string.h"

void *
memmove(void *dest, const void *src, size_t n)
{
    // check if memcpy can be used (not overlaped)
    if (abs(dest - src) > n)
        return memcpy(dest, src, n);

    void *temp = malloc(n + 1);
    assert(temp != NULL);

    memcpy(temp, src, n);
    memcpy(dest, temp, n);
    free(temp);

    return dest;
}
