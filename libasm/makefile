CC = gcc
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
DEFS = def_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS} ${DB_FLAGS}

.DELETE_ON_ERROR:

.PHONY: clean

all:

tests: test_0

test-0: asm-0
	${CCMD} ${DEFS} test_0.c -o run_test_0

asm-0:
	nasm -f elf64 0-strlen.asm -o 0-strlen.o

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_*
