CC = gcc
GDB = cgdb

# CUNIT = $(shell pkg-config -cflags -libs cunit)
# CRITERION = $(shell pkg-config -cflags -libs criterion)
# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)

CFLAGS = -Wall -Werror -Wextra -pedantic
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${I_FLAGS} ${L_FLAGS} ${DB_FLAGS}

BINDIR = build
TESTDIR = tests
DEFDIR = defs
HEADIR = headers
DEFS = $(shell find ${DEFDIR}/*.c)

MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all

.DELETE_ON_ERROR:

.PHONY: clean clean-obj defs

all: hnm

hnm: 
	${CCMD} *.c -o hnm

defs:

######## UTILITY 

clean:
	$(RM) -v *~ *.exec *.o *.out *.x  *-hreadelf defs/*.o hnm

clean-obj:
	$(RM) -v *~ *.o defs/*.o
