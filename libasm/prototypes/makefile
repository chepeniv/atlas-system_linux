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

hello:
	${AS} hello.asm 
	ld hello.o -o hello.x
	./hello.x

add:
	${ASD} dbl.asm
	${ASD} add.asm 
	${CCMD} -c add_test.c -o add_test.o
	${CCMD} add.o dbl.o add_test.o -o add.x 
	./add.x 17 83

add_print:
	${ASD} add_print.asm 
	gcc add_print.o
	./a.out

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
