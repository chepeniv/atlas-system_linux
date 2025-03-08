CC = gcc
GDB = cgdb
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
DEFS = def_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${DB_FLAGS}
AS = nasm -f elf64
ASD = ${AS} -g # -F dwarf
LD = ld

.DELETE_ON_ERROR:

.PHONY: clean

######## GLOBAL

all:

tests: test_0

asm: asm-0

######## ASM TESTING

test-0: clean asm-0
	${CCMD} -c tests/test_0.c 
	${CCMD} test_0.o 0-strlen.o -o test_0.run
	${GDB} test_0.run

######## ASM TASKS

asm-0:
	${ASD} 0-strlen.asm

######## UTILITY

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
