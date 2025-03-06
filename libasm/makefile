CC = gcc
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
DEFS = def_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${DB_FLAGS}
AS = nasm -f elf64
ASD = ${AS} -g -F dwarf
LD = ld

.DELETE_ON_ERROR:

.PHONY: clean

all:

######## GLOBAL

tests: test_0

asm: asm-0

######## ASM TESTING

test-0: asm-0
	${CCMD} ${DEFS} test_0.c -o run_test_0

######## ASM TASKS

asm-0:
	nasm -f elf64 0-strlen.asm -o 0-strlen.o

######## x86-64 asm TESTING

hello:
	${ASD} hello.asm 
	ld hello.o -o hello.x
	./hello.x

add:
	${ASD} add.asm 
	${CCMD} -c test_add.c -o test_add.o
	${LD} add.o test_add.o -o add.x
	${MEMTEST} ./add.x 7 8

######## UTILITY

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
