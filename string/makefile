
# Generic lib makefile
# OUTPUT have to be changed
# All .c files withot 'test'
# in their name would be compiled
# into OUTPUT library.

CC= gcc -Wall
AR= ar rcs
OUTPUT = libstring.a
SRCS = $(filter-out %test%.c $(wildcard *.c))
OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(AR) $(OUTPUT) $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $<

cleanall: clean
	rm   -f $(OUTPUT)

clean:
	rm -f *.o *~
