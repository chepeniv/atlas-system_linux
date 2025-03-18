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

######## CORE TASKS

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

######## ADVANCED TASKS

12-task:
	${CCMD} 100-all_in_one.c ${TESTDIR}/test-100.c -o ${BINDIR}/adv_100.x

13-task:
	${CCMD} 101-sigset_init.c ${TESTDIR}/test-101.c -o ${BINDIR}/adv_101.x

14-task:
	${CCMD} 102-signals_block.c ${TESTDIR}/test-102.c -o ${BINDIR}/adv_102.x

15-task:
	${CCMD} 103-signals_unblock.c ${TESTDIR}/test-103.c -o ${BINDIR}/adv_103.x

16-task:
	${CCMD} 104-handle_pending.c ${TESTDIR}/test-104.c -o ${BINDIR}/adv_104.x

######## UTILITY 

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start run-*
