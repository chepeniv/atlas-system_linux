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

all: test_0 test_1

asm: asm-0 asm-1

######## ASM TESTING

test-0: clean asm-0
	${CCMD} -c tests/test_0.c 
	${CCMD} test_0.o 0-strlen.o -o test_0.run
	# ${GDB} test_0.run

test-1: clean asm-1
	${CCMD} -c tests/test_1.c 
	${CCMD} test_1.o 1-strcmp.o -o test_1.run
	# ./test_1.run

test-2: clean asm-2
	${CCMD} -c tests/test_2.c 
	${CCMD} test_2.o 2-strncmp.o -o test_2.run
	./test_2.run

######## ASM TASKS

asm-0:
	${ASD} 0-strlen.asm

asm-1:
	${ASD} 1-strcmp.asm

asm-2:
	${ASD} 2-strncmp.asm

######## UTILITY

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
