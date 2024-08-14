#include "lowlevel.h"
#define TESTLOWLEVEL 1

#if TESTLOWLEVEL

#include "../assert/assert.h"
#include "math.h"
#include <stdio.h> // sorry

int
main()
{
    int  a = 10;
    long b = -2;

    assert(a == abs(a));
    assert(a == abs(__inv(a)));
    assert(!__is_negative_int(a));

    assert(b == absl(b));
    assert(b == absl(__inv(b)));
    assert(__is_negative_long(b));

    puts("All test passed");
}

#endif
