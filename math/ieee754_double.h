#ifndef _IEEE754_DOUBLE_H
#define _IEEE754_DOUBLE_H 1

typedef struct
{
    unsigned      sign : 1;
    unsigned      exponent : 11;
    unsigned long mantissa : 52;
} __ieee754_double;

/*
 * DOUBLE type DEFINITIONS and MACROS
 */


#define IEEE754_DOUBLE_ZERO_POS                  \
    (__ieee754_double)                           \
    {                                            \
        .sign = 0, .exponent = 0, .mantissa = 0, \
    }

#define IEEE754_DOUBLE_ZERO_NEG                  \
    (__ieee754_double)                           \
    {                                            \
        .sign = 1, .exponent = 0, .mantissa = 0, \
    }

#define IEEE754_DOUBLE_INF_POS                       \
    (__ieee754_double)                               \
    {                                                \
        .sign = 0, .exponent = 0x7FF, .mantissa = 0, \
    }

#define IEEE754_DOUBLE_INF_NEG                       \
    (__ieee754_double)                               \
    {                                                \
        .sign = 1, .exponent = 0x7FF, .mantissa = 0, \
    }

#define DOUBLE_SIGN_MASK     0x8000000000000000
#define DOUBLE_EXPONENT_MASK 0x7FF0000000000000
#define DOUBLE_MATISSA_MASK  0x000FFFFFFFFFFFFF
#define DOUBLE_UNSIGNED_MASK (DOUBLE_EXPONENT_MASK & DOUBLE_MATISSA_MASK)

#define iee754_double_is_zero(n) \
    (((__ieee754_double) (n) & (DOUBLE_UNSIGNED_MASK)) == (IEEE754_DOUBLE_ZERO_POS))

#define ieee754_double_is_inf_pos(n) \
    (__ieee754_double) (n) == (IEEE754_DOUBLE_INF_POS))

#define ieee754_double_is_inf_neg(n) \
    (__ieee754_double) (n) == (IEEE754_DOUBLE_INF_NEG))

#define ieee754_double_is_inf_unsigned(n) \
    (((__ieee754_double) (n) & (DOUBLE_UNSIGNED_MASK)) == (IEEE754_DOUBLE_INF_POS))

#define ieee754_is_negative_double(n) (!(n & DOUBLE_SIGN_MASK))

#endif
