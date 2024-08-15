#include "math.h"

Float
ieee754_add_float(Float a, Float b)
{
    int exp_a = FLOAT_REAL_EXP(a);
    int exp_b = FLOAT_REAL_EXP(b);

    long mant_a, mant_b;

    if (exp_a < exp_b)
    {
        mant_a = exp_a << (exp_b - exp_a);
        mant_b = exp_b;
    }
    else if (exp_a > exp_b)
    {
        mant_a = exp_a;
        mant_b = exp_b << (exp_a - exp_b);
    }
    else
    {
        mant_a = a.mantissa;
        mant_b = b.mantissa;
    }
}

Float
ieee754_subs_float(Float a, Float b)
{
}

Float
ieee754_mult_float(Float a, Float b)
{
}

Float
ieee754_div_float(Float a, Float b)
{
}
