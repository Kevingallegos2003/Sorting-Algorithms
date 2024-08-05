# Makefile for CSE 13S, Spring 2023, Assignment 3

# DO NOT EDIT THIS FILE

# Usage:
#
#    $ make             Make the sorting program (ready for LLDB debugging).
#    $ make all
#
#    $ make clean       Type this command after editing this Makefile or
#                       when switching between all and release targets.
#
#    $ make format      Run clang-format on *.c and *.h
#
#    $ make release     Make the sorting program (without debugging info).
#                       We use this for the reference design.


CC=clang
debug:   CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g
release: CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS=-lm

EXECBIN=sorting
OBJS=\
    batcher.o \
    heap.o \
    insert.o \
    quick.o \
    set.o \
    shell.o \
    sorting.o \
    stats.o \


.PHONY: all debug release clean

all: debug

debug: $(EXECBIN)

release: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i --style=file *.[ch]
