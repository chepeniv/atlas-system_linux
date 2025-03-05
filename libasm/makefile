CC = gcc
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
DEFS = def_*.c
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS} ${DB_FLAGS}

AS = nasm -f elf64
ASD = -g -F dwarf

.DELETE_ON_ERROR:

.PHONY: clean

all:

tests: test_0

test-0: asm-0
	${CCMD} ${DEFS} test_0.c -o run_test_0

asm-0:
	nasm -f elf64 0-strlen.asm -o 0-strlen.o

hello:
	${AS} ${ASD} hello.asm 
	ld hello.o -o hello.x
	./hello.x

# add:
# 	nasm -f elf64 add.asm 
# 	ld add.o -o add.x

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
