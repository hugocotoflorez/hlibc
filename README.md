# hlibc

## About

glibc "clone". I made this to have libs written by my own
without dependencies to use in proyects that dont have access
to glibc.

> The Hugo's C Library is distributed in the hope that it will be useful,
> but WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


## Implemented stuff

### string

- [x] memcmp
- [x] memcpy
- [x] memmove
- [x] memset
- [x] __memcmpeq
- [x] strcpy
- [x] strncpy
- [x] strcat
- [x] strncat
- [x] strcmp
- [x] strncmp
- [x] strlen
- [x] strnlen

### stddef

- [x] null
- [x] size_t
- [x] ssize_t
- [x] BIGGEST_TYPE: (no glibc)

### assert

- [x] assert

### malloc

- [x] free
- [x] malloc
- [x] calloc
- [x] realloc

### stdio

- File I/O
- [x] fopen
- [x] fclose
- [x] fflush

- VA ARGS
- [x] va_list
- [x] va_start
- [x] va_end
- [x] va_arg

### math

- math.h
    - [x] abs(int)
    - [x] absl(long)

- ieee754.h

- lowlevel.h
    - [x] __is_negative_int / long
    - [x] __inv  (1 <-> -1)


### errno

Todo: append errcodes as needed


