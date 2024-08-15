#ifndef _LOWLEVEL_H
#define _LOWLEVEL_H

/* for float low level see ./iee754.h
 */

#define INTSIZE  32
#define LONGSIZE 64

#define __is_negative_int(n)  ((n) >> (INTSIZE - 1))
#define __is_negative_long(n) ((n) >> (LONGSIZE - 1))
#define __inv(n)              ((~(n)) + 0x1)

#endif
