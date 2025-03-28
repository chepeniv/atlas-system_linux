CC      := gcc
GDB     := cgdb

CFLAGS  := -Wall -Werror -Wextra -pedantic -std=c99 
CDEBUG  := -ggdb3
CLINK   := -shared -fPIC
CPY     := $(shell pkg-config -cflags -libs python3)
CCMD    := ${CC} ${CFLAGS} ${CDEBUG} ${CLINK} ${CPY}

BINDIR  := build
TESTDIR := tests
DEFDIR  := defs
HEADIR  := headers

VALFL   := -s --track-origins=yes --leak-check=full --show-leak-kinds=all
MEMTEST := valgrind ${VALFL}

.DELETE_ON_ERROR:

.PHONY: clean clean-obj defs

all: clean 1-task 2-task 3-task 4-task 5-task

######## TASKS

1-task: 
	${CCMD} -Wl,-soname=PyList -o libPyList.so 1-python.c

defs:

######## TESTING

test: 

memtest: 

######## UTILITY 

betty: 
	echo "running Betty coding style checks..."
	@betty-style *.c *.h
	echo "running Betty documentation checks..."
	@betty-doc *.c *.h

clean:
	@$(RM) -v *~ *.exec *.o *.out *.x  *.c 

clean-obj:
	@$(RM) -v *~ *.o 
