CC      := gcc
GDB     := cgdb

CFLAGS  := -Wall -Werror -Wextra -pedantic 
# -std=c99
CDEBUG  := -ggdb3
CCMD    := ${CC} ${CFLAGS} ${CDEBUG} 

VALFL   := -s --track-origins=yes --leak-check=full --show-leak-kinds=all
MEMTEST := valgrind ${VALFL}

.DELETE_ON_ERROR:

.PHONY: clean clean-obj clean-lib betty

######## TASKS

exercise_0:
	${CCMD} exercise_0.c -o exercise_0.exec

######## RUN

run_0: exercise_0
	./exercise_0.exec /usr/bin/echo "successful run"

######## memory checks

memtest_0:
	${MEMTEST} ./exercise_0.exec /usr/bin/echo "hello, world!"

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
