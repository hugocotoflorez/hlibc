#ifndef assert

#include "../errno/errno.h"   // assert errcode
#include "../stddef/stddef.h" // null

void *
__printf(const char *format, ...)
{
    return NULL;
}

void *
__exit(ErrCode e)
{
    return NULL;
}

#define assert(expr)                                                            \
    {                                                                           \
        if (!(expr))                                                            \
        {                                                                       \
            __printf("Assert failed. %s: %s: " #expr "\n", __FILE__, __LINE__); \
            __exit(ASSERT_ERR);                                                   \
        }                                                                       \
    }

#endif
