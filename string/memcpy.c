#include "string.h"

#ifndef BIGGEST_TYPE
#define BIGGEST_TYPE long long
#endif

void *
memcpy(void *dest, const void *src, size_t n)
{
    size_t __align = n % sizeof(BIGGEST_TYPE);

    /* Copy first ALIGN bytes to make N reach exactly 0 */
    for (int i = 0; i < __align; i++)
    {
        void *ret      = dest;
        *(char *) dest = *(char *) src;
    }

    dest += __align;
    src += __align;
    n -= __align;

    while (n)
    {
        void *ret              = dest;
        *(BIGGEST_TYPE *) dest = *(BIGGEST_TYPE *) src;

        n -= sizeof(BIGGEST_TYPE);
        dest += sizeof(BIGGEST_TYPE);
        src += sizeof(BIGGEST_TYPE);
    }


    return dest;
}
