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
	${CCMD} 0-handle_signal.c tests/test-0.c -o ${BINDIR}/run-0
	${BINDIR}/run-0

2-task:
	${CCMD} 2-handle_sigaction.c tests/test-2.c -o ${BINDIR}/run-2
	${BINDIR}/run-2

4-task:
	${CCMD} 4-trace_signal_sender.c tests/test-4.c -o ${BINDIR}/run-4
	${BINDIR}/run-4

5-task:
	${CCMD} 5-signal_describe.c -o ${BINDIR}/describe.x

6-task:
	${CCMD} 6-suspend.c -o ${BINDIR}/suspend.x
	${BINDIR}/suspend.x

7-task:
	${CCMD} 7-signal_send.c -o ${BINDIR}/sigsend.x

10-task:
	${CCMD} 10-pid_exist.c ${TESTDIR}/test-10.c -o ${BINDIR}/pid_exist.x

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start run-*
