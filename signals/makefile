CC = gcc
GDB = cgdb

CUNIT = $(shell pkg-config -cflags -libs cunit)
CRITERION = $(shell pkg-config -cflags -libs criterion)

CFLAGS = -Wall -Werror -Wextra -pedantic 
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${DB_FLAGS}

OBJ = *.o
RUN = ./run-*

MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all

.DELETE_ON_ERROR:

.PHONY: clean

######## GLOBAL

all: 

0-task:
	${CCMD} 0-handle_signal.c tests/test-0.c -o run-0
	# ./run-0

2-task:
	${CCMD} 2-handle_sigaction.c tests/test-2.c -o run-2
	./run-2

4-task:
	${CCMD} 4-trace_signal_sender.c tests/test-4.c -o run-4
	./run-4

5-task:
	${CCMD} 5-signal_describe.c -o describe.x

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start run-*
