#ifndef _ERRNO_H
#define _ERRNO_H 1

typedef enum __errno_errcodes
{
    SUCCESS = 0,
    ASSERT_ERR,
    IEE754_OVERFLOW,
    IEE754_UNDERFLOW,
    IEE754_INEXACT,
    IEE754_INVALID,
    IEE754_DIV0,
    ENOMEM, // out of memory
} ErrCode;

static ErrCode errno;

#endif
