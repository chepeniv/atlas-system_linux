CC      := gcc
GDB     := cgdb

CFLAGS  := -Wall -Werror -Wextra -pedantic -std=c99
CDEBUG  := -ggdb3
CLINK   := -shared -fPIC
LIBPY   := -Wl,-soname=libPython -o libPython.so
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

build_1:
	${CCMD} -Wl,-soname=PyList -o libPyList.so 1-python.c
	cp libPyList.so tests/

build_2:
	${CCMD} ${LIBPY} 2-python.c
	cp libPython.so tests/

build_3:
	${CCMD} ${LIBPY} 3-python.c
	cp libPython.so tests/

defs:

######## TESTING

test_1:
	python3 tests/test-1.py

test_2:
	python3 tests/test-2.py

test_3:
	python3 -u tests/test-3.py

######## memory checks

1-memtest:
	${MEMTEST} python3 tests/test-1.py

######## UTILITY

betty:
	@echo "running Betty CODING STYLE checks..."
	@betty-style *.c *.h
	@echo "running Betty DOCUMENTATION checks..."
	@betty-doc *.c *.h

clean: clean-obj clean-lib
	@$(RM) -v *~ *.exec *.out *.x

clean-obj:
	@$(RM) -v *.o

clean-lib:
	@$(RM) -v *.so
