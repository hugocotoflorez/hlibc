#ifndef _ASSERT_H

#include "../errno/errno.h" // assert errcode

#define __exit_msg(msg) \
    {                   \
        /* TODO */      \
    }

#define assert(expr)                     \
    {                                    \
        if (!(expr))                     \
            __exit_msg(ASSERT_ERR, msg); \
    }

#endif
