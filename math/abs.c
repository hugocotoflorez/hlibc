#include "lowlevel.h"
#include "math.h"

int
abs(int n)
{
    if (__is_negative_int(n))
        return __inv(n);
    else
        return n;
}

long
absl(long n)
{
    if (__is_negative_long(n))
        return __inv(n);
    else
        return n;
}

float
absf(float n)
{
    return n;
}

double
absd(double n)
{
    return n;
}
