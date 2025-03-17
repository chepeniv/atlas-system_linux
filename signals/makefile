CC = gcc
GDB = cgdb

CUNIT = $(shell pkg-config -cflags -libs cunit)
CRITERION = $(shell pkg-config -cflags -libs criterion)

CFLAGS = -Wall -Werror -Wextra -pedantic 
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${DB_FLAGS}

OBJ = *.o
RUN = ./run-*
BINDIR = build
TESTDIR = tests

MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all

.DELETE_ON_ERROR:

.PHONY: clean

######## GLOBAL

all: 

0-task:
	${CCMD} 0-handle_signal.c tests/test-0.c -o build/run-0
	build/run-0

2-task:
	${CCMD} 2-handle_sigaction.c tests/test-2.c -o build/run-2
	build/run-2

4-task:
	${CCMD} 4-trace_signal_sender.c tests/test-4.c -o build/run-4
	build/run-4

5-task:
	${CCMD} 5-signal_describe.c -o build/describe.x

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start run-*
