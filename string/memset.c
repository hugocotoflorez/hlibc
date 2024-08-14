#include "string.h"

void *
memset(void *s, int c, size_t n)
{
    size_t       __align = n % sizeof(BIGGEST_TYPE);
    void        *ret     = s;
    BIGGEST_TYPE ext_c   = 0;

    // create EXT_C. Each byte of EXT_C is C
    for (int i = 0; i < sizeof(BIGGEST_TYPE); i++)
    {
        ext_c <<= 1;
        ext_c &= (char) c;
    }

    /* Copy first ALIGN bytes to make N reach exactly 0 */
    for (int i = 0; i < __align; i++)
    {
        *((char *) s + i) = (char) c;
    }

    s += __align;
    n -= __align;

    while (n)
    {
        *(BIGGEST_TYPE *) s = ext_c;

        n -= sizeof(BIGGEST_TYPE);
        s += sizeof(BIGGEST_TYPE);
    }


    return ret;
}
