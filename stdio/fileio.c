#include "../malloc/malloc.h"
#include "../string/string.h"
#include "stdio.h"
#include <fcntl.h>  // open
#include <unistd.h> // close

int
__get_flags(const char *mode)
{
    int flags = 0;

    if (!strcmp(mode, "r"))
        flags |= O_RDONLY;
    if (!strcmp(mode, "r+"))
        flags |= O_RDWR;
    if (!strcmp(mode, "w"))
        flags |= O_WRONLY | O_TRUNC | O_CREAT;
    if (!strcmp(mode, "w+"))
        flags |= O_RDWR | O_TRUNC | O_CREAT;
    if (!strcmp(mode, "a"))
        flags |= O_WRONLY | O_CREAT;
    if (!strcmp(mode, "a+"))
        flags |= O_RDWR | O_CREAT;

    return flags;
}

FILE *
__create_file(int fd)
{
    FILE *f = malloc(sizeof(FILE));
    if (f)
        *f = (FILE){ .fd = fd };
    return f;
}

FILE *
fopen(const char *pathname, const char *mode)
{
    int fd = -1;
    int flags;

    flags = __get_flags(mode);

    if (flags)
        fd = open(pathname, flags);

    if (fd < 0)
        return NULL;

    return __create_file(fd);
}

int
fclose(FILE *stream)
{
    close(stream->fd);
    free(stream);
    return 0;
}

int
fflush(FILE *stream)
{
    return fsync(stream->fd);
}
