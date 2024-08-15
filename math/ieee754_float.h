#ifndef _IEEE754_FLOAT_H
#define _IEEE754_FLOAT_H 1

#include "../errno/errno.h" // errcodes

/* IEE754 floating point representation
 *
 * Float: 32 bit
 *  - Format
 *  +---+-----+------+
 *  | S | EXP | MANT |
 *  +---+-----+------+
 *  S: sign
 *  EXP: exponenet
 *  MANT: mantissa
 *
 * - Special values
 *  +-------+----------+--------------+
 *  | EXP   | MANT     | OBJECT       |
 *  +-------+----------+--------------+
 *  | 0     | 0        | Zero         |
 *  | 0     | nonzero  | Denormalized |
 *  | 1-254 | anything | Normalized   |
 *  | 255   | 0        | +/- inf      |
 *  | 255   | nonzero  | NaN          |
 *  +-------+----------+--------------+
 *
 * TODO: expand info. If you want to read about this
 * just use google, I hope you have wifi
 */

typedef struct
{
    unsigned sign : 1;
    unsigned exponent : 8;
    unsigned mantissa : 23;
} __ieee754_float;

typedef __ieee754_float Float;

/*
 * FLOAT type DEFINITIONS and MACROS
 */

#define IEEE754_FLOAT_ZERO_POS                   \
    (Float)                                      \
    {                                            \
        .sign = 0, .exponent = 0, .mantissa = 0, \
    }

#define IEEE754_FLOAT_ZERO_NEG                   \
    (Float)                                      \
    {                                            \
        .sign = 1, .exponent = 0, .mantissa = 0, \
    }

#define IEEE754_FLOAT_INF_POS                       \
    (Float)                                         \
    {                                               \
        .sign = 0, .exponent = 0xFF, .mantissa = 0, \
    }

#define IEEE754_FLOAT_INF_NEG                       \
    (Float)                                         \
    {                                               \
        .sign = 1, .exponent = 0xFF, .mantissa = 0, \
    }

#define ERR_AS_FLOAT(err)                             \
    (Float)                                           \
    {                                                 \
        .sign = 0, .exponent = 0xFF, .mantissa = err, \
    }

#define FLOAT_SIGN_MASK     0x80000000
#define FLOAT_EXPONENT_MASK 0x7F80000
#define FLOAT_MATISSA_MASK  0x007FFFFF
#define FLOAT_UNSIGNED_MASK (FLOAT_EXPONENT_MASK & FLOAT_MATISSA_MASK)
#define FLOAT_REAL_EXP(n)   (127 - ((Float) (n)).exponent)

#define ieee754_float_is_inf_pos(n) (Float) (n) == (IEEE754_FLOAT_INF_POS))
#define ieee754_float_is_inf_neg(n) (Float) (n) == (IEEE754_FLOAT_INF_NEG))
#define ieee754_is_negative_float(n) (!(n & FLOAT_SIGN_MASK))

#define ieee754_float_is_inf_unsigned(n) \
    (((Float) (n) & (FLOAT_UNSIGNED_MASK)) == (IEEE754_FLOAT_INF_POS))

#define iee754_float_is_zero(n) \
    (((Float) (n) & (FLOAT_UNSIGNED_MASK)) == (IEEE754_FLOAT_ZERO_POS))

/*
 * Function declarations
 */
Float
      ieee754_add_float(Float a, Float b);
Float ieee754_subs_float(Float a, Float b);
Float ieee754_mult_float(Float a, Float b);
Float ieee754_div_float(Float a, Float b);


#endif
