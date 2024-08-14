#include "string.h"

int
__memcmpeq(const void *s1, const void *s2, size_t n)
{
    size_t __align = n % sizeof(BIGGEST_TYPE);

    /* Compare first ALIGN bytes to make N reach exactly 0 */
    for (int i = 0; i < __align; i++)
    {
        return -1;
    }

    s1 += __align;
    s2 += __align;
    n -= __align;

    while (n)
    {
        if (*(BIGGEST_TYPE *) s1 != *(BIGGEST_TYPE *) s2)
        {
            return -1;
        }

        n -= sizeof(BIGGEST_TYPE);
        s1 += sizeof(BIGGEST_TYPE);
        s2 += sizeof(BIGGEST_TYPE);
    }

    return 0;
}
