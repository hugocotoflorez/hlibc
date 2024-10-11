#include "../string/string.h"
#include "stddef.h"
#include "stdio.h"
#include <fcntl.h>
#include <unistd.h>

// TODO
void __parse_int(int fd, const char **format, va_list va, int flags);
void __parse_str(int fd, const char **format, va_list va, int flags);
void __parse_char(int fd, const char **format, va_list va, int flags);
void __parse_float(int fd, const char **format, va_list va, int flags);
void __parse_unsigned(int fd, const char **format, va_list va, int flags);

typedef enum
{
    NOFLAG = 0,
    ALTFORM,
    ZEROPAD,

} format_flags;

/* Given a format (format HAVE TO start with %)
 * write a formatted arg to the given file descriptor.
 * format is updated to the first char after format sequence */
void
__format_write(int fd, const char **format, va_list *va)
{
    signed char  esc   = 0;
    format_flags flags = NOFLAG;

    ++*format; // current is %

    while (!esc)
        ;
    switch (**format)
    {
        case 'b':
        case '#':
        case '0':
        case '-':
        case ' ':
        case '+':
        case '\'':
        case 'I':
        case '*':
        case '.':
        case 'h':
        case 'l':
        case 'q':
        case 'L':
        case 'j':
        case 'z':
        case 'Z':
        case 't':

        case 'e': // idk what is this
        case 'E':
        case 'a':
        case 'A':
        case '%':

            ++*format; // Not implemented
            break;

        case 'd':
        case 'i':
            __parse_int(fd, format, va, flags);
            break;

        case 'p': // idk
        case 'o':
        case 'u':
        case 'x':
        case 'X':
            __parse_unsigned(fd, format, va, flags);
            break;

        case 'f':
        case 'F':
            __parse_float(fd, format, va, flags);
            break;

        case 'c':
            __parse_char(fd, format, va, flags);
            break;

        case 's':
            __parse_str(fd, format, va, flags);
            break;


        default:
            // **format is not part of
            // formatting sequence
            esc = 1;
    }
}

int printf(const char *format, ...);
#define printf(format, ...) fprintf(stdout, format, ##__VA_ARGS__)

int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char str, size_t size, const char *format, ...);

int
fprintf(FILE *stream, const char *format, ...)
{
    va_list va;
    va_start(va, format);
    char *buf[WBUFLEN];
    char *b   = (char *) buf;
    int   ret = 0;
    int   offset;

    while (*format)
    {
        if (*format != '%')
        {
            *b = *format;
            ++b;
            if (b - (char *) buf == WBUFLEN)
            {
                write(stream->fd, buf, WBUFLEN);
                ret += WBUFLEN;
                b = (char *) buf;
            }
        }
        else
            __format_write(stream->fd, &format, &va);
    }
    offset = b - (char *) buf;
    if (offset > 0)
    {
        ret += offset;
        write(stream->fd, buf, offset);
    }

    return ret;
}
