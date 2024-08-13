/* Author: Hugo Coto Florez.
 * This file is part of the Hugo's C Library.
 *
 * The Hugo's C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _STRING_H
#define _STRING_H 1


/* Get size_t and NULL from <stddef.h>.  */
#include "../stddef/stddef.h"


/* Copy N bytes of SRC to DEST.  */
extern void *memcpy(void *dest, const void *src, size_t n);

/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern void *memmove(void *dest, const void *src, size_t n);

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
extern void *memccpy(void *dest, const void *src, int c, size_t n);

/* Set N bytes of S to C.  */
extern void *memset(void *s, int c, size_t n);

/* Compare N bytes of S1 and S2.  */
extern int memcmp(const void *s1, const void *s2, size_t n);

/* Compare N bytes of S1 and S2.  Return zero if S1 and S2 are equal.
   Return some non-zero value otherwise.

   Essentially __memcmpeq has the exact same semantics as memcmp
   except the return value is less constrained.  memcmp is always a
   correct implementation of __memcmpeq.  As well !!memcmp, -memcmp,
   or bcmp are correct implementations.

   __memcmpeq is meant to be used by compilers when memcmp return is
   only used for its boolean value.

   __memcmpeq is declared only for use by compilers.  Programs should
   continue to use memcmp.  */
extern int __memcmpeq(const void *s1, const void *s2, size_t n);

/* Search N bytes of S for C.  */
extern void *memchr(const void *s, int c, size_t n);

/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
extern void *rawmemchr(const void *s, int c);

/* Search N bytes of S for the final occurrence of C.  */
extern void *memrchr(const void *s, int c, size_t n);

/* Copy SRC to DEST.  */
extern char *strcpy(char *dest, const char *src);

/* Copy no more than N characters of SRC to DEST.  */
extern char *strncpy(char *dest, const char *src, size_t n);

/* Append SRC onto DEST.  */
extern char *strcat(char *dest, const char *src);

/* Append no more than N characters from SRC onto DEST.  */
extern char *strncat(char *dest, const char *src, size_t n);

/* Compare S1 and S2.  */
extern int strcmp(const char *s1, const char *s2);

/* Compare N characters of S1 and S2.  */
extern int strncmp(const char *s1, const char *s2, size_t n);

/* Duplicate S, returning an identical malloc'd string.  */
extern char *strdup(const char *s);

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
extern char *strndup(const char *string, size_t n);

/* Duplicate S, returning an identical alloca'd string.  */
// glibc definition
#define strdupa(s)                                            \
    (__extension__({                                          \
        const char *__old = (s);                              \
        size_t      __len = strlen(__old) + 1;                \
        char       *__new = (char *) __builtin_alloca(__len); \
        (char *) memcpy(__new, __old, __len);                 \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
// glibc definition
#define strndupa(s, n)                                            \
    (__extension__({                                              \
        const char *__old = (s);                                  \
        size_t      __len = strnlen(__old, (n));                  \
        char       *__new = (char *) __builtin_alloca(__len + 1); \
        __new[__len]      = '\0';                                 \
        (char *) memcpy(__new, __old, __len);                     \
    }))

/* Find the first occurrence of C in S.  */
extern char *strchr(const char *s, int c);

/* Find the last occurrence of C in S.  */
extern char *strrchr(const char *s, int c);

/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
extern char *strchrnul(const char *s, int c);

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
extern size_t strcspn(const char *s, const char *reject);

/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
extern size_t strspn(const char *s, const char *accept);

/* Find the first occurrence in S of any character in ACCEPT.  */
extern char *strpbrk(const char *s, const char *accept);

/* Find the first occurrence of NEEDLE in HAYSTACK.  */
extern char *strstr(const char *haystack, const char *needle);

/* Divide S into tokens separated by characters in DELIM.  */
extern char *strtok(char *s, const char *delim);

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
extern char *strtok_r(char *s, const char *delim, char **save_ptr);

/* Similar to `strstr' but this function ignores the case of both strings. */
extern char *strcasestr(const char *haystack, const char *needle);

/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
extern void *
memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
extern void *mempcpy(void *dest, const void *src, size_t n);

/* Return the length of S.  */
extern size_t strlen(const char *s);

/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN. */
extern size_t strnlen(const char *string, size_t maxlen);

/* Return a string describing the meaning of the `errno' code in ERRNUM. */
extern char *strerror(int errnum);

/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.If a temporary buffer is required, at most BUFLEN bytes of BUF
   will be used.  */
extern char *strerror_r(int errnum, char *buf, size_t buflen);

/* Return a string describing the meaning of the error in ERR.  */
extern const char *strerrordesc_np(int err);
/* Return a string with the error name in ERR.  */
extern const char *strerrorname_np(int err);

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
extern void explicit_bzero(void *s, size_t n);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
extern char *strsep(char **stringp, const char *delim);

/* Return a string describing the meaning of the signal number in SIG.  */
extern char *strsignal(int sig);

/* Return an abbreviation string for the signal number SIG.  */
extern const char *sigabbrev_np(int sig);

/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
extern const char *sigdescr_np(int sig);

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST. */
extern char *stpcpy(char *dest, const char *src);

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
extern char *stpncpy(char *dest, const char *src, size_t n);

/* Copy at most N - 1 characters from SRC to DEST.  */
extern size_t strlcpy(char *dest, const char *src, size_t n);

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
extern size_t strlcat(char *dest, const char *src, size_t n);

/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
extern int strverscmp(const char *s1, const char *s2);

/* Sautee STRING briskly.  */
extern char *strfry(char *string);

/* Frobnicate N bytes of S.  */
extern void *memfrob(void *s, size_t n);

/* Return the file name within directory of FILENAME. */
extern char *basename(const char *filename);

#endif /* string.h  */
