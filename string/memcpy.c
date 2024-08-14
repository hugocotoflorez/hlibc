#include "string.h"

void *
memcpy(void *dest, const void *src, size_t n)
{
    size_t __align = n % sizeof(BIGGEST_TYPE);
    void  *ret     = dest;

    /* Copy first ALIGN bytes to make N reach exactly 0 */
    for (int i = 0; i < __align; i++)
    {
        *((char *) dest + i) = *((char *) src + i);
    }

    dest += __align;
    src += __align;
    n -= __align;

    while (n)
    {
        *(BIGGEST_TYPE *) dest = *(BIGGEST_TYPE *) src;

        n -= sizeof(BIGGEST_TYPE);
        dest += sizeof(BIGGEST_TYPE);
        src += sizeof(BIGGEST_TYPE);
    }


    return ret;
}
