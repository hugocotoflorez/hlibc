#ifndef _MATH_H
#define _MATH_H 1

#include "ieee754.h"
#include "lowlevel.h"

#define M_Ef 2.7182818284590452354f         /* e */
#define M_LOG2Ef 1.4426950408889634074f     /* log_2 e */
#define M_LOG10Ef 0.43429448190325182765f   /* log_10 e */
#define M_LN2f 0.69314718055994530942f      /* log_e 2 */
#define M_LN10f 2.30258509299404568402f     /* log_e 10 */
#define M_PIf 3.14159265358979323846f       /* pi */
#define M_PI_2f 1.57079632679489661923f     /* pi/2 */
#define M_PI_4f 0.78539816339744830962f     /* pi/4 */
#define M_1_PIf 0.31830988618379067154f     /* 1/pi */
#define M_2_PIf 0.63661977236758134308f     /* 2/pi */
#define M_2_SQRTPIf 1.12837916709551257390f /* 2/sqrt(pi) */
#define M_SQRT2f 1.41421356237309504880f    /* sqrt(2) */
#define M_SQRT1_2f 0.70710678118654752440f  /* 1/sqrt(2) */

extern int    abs(int n);
extern long   absl(long n);
extern float  absf(float n);
extern double absd(double n);

#endif
