#ifndef assert

#include "../errno/errno.h"   // assert errcode
#include "../stddef/stddef.h" // null
#include "../stdio/stdio.h"

extern void *exit(ErrCode e); // TODo

#define assert(expr)                                                          \
    {                                                                         \
        if (!(expr))                                                          \
        {                                                                     \
            printf("Assert failed. %s: %s: " #expr "\n", __FILE__, __LINE__); \
            exit(ASSERT_ERR);                                                 \
        }                                                                     \
    }

#endif
