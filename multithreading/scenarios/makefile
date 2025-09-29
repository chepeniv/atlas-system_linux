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

######## SCENARIOS

scenario_0: clean
	$(CCMD) ../0-thread_entry.c 0-test.c -o 0-test.x
	./0-test.x

scenario_1: clean
	$(CCMD) ../1-tprintf.c 1-test.c -o 1-test.x
	./1-test.x

scenario_4: clean
	$(CCMD) ../20-tprintf.c 4-test.c -o 4-test.x
	./4-test.x

scenario_5: clean
	$(CCMD) ../21-prime_factors.c ../list.c 5-test.c -lm -o 5-test.x
	./5-test.x 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
	./5-test.x 18446744073709551609 18446744073709551608 18446744073709551612 

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
