CC      := gcc
GDB     := cgdb

CFLAGS  := -Wall -Werror -Wextra -pedantic 
# -std=c99
CDEBUG  := -ggdb3
CCMD    := ${CC} ${CFLAGS} ${CDEBUG} 

BINDIR  := bin
TESTDIR := test
DEFDIR  := def
HEADDIR  := include

VALFL   := -s --track-origins=yes --leak-check=full --show-leak-kinds=all
MEMTEST := valgrind ${VALFL}

.DELETE_ON_ERROR:

.PHONY: clean clean-obj clean-lib betty

######## TASKS

build_0: clean
	${CCMD} 0-thread_entry.c -o 0-bin.x

######## RUN

run_0: build_0

######## TESTING

test_0:
	@echo no test currently exist

######## memory checks

memtest_0:
	# ${MEMTEST} 

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
