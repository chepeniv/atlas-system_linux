CC = gcc
GDB = cgdb
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${DB_FLAGS}
AS = nasm -f elf64
ASD = ${AS} -g # -F dwarf
LD = ld

OBJ = *.o
RUN = ./*.run

.DELETE_ON_ERROR:

.PHONY: clean

######## GLOBAL

all: asm

asm: asm-0 asm-1 asm-2 asm-3 asm-4 asm-5 asm-6 asm-7 asm-8 asm-9

######## ASM TESTING

test-0: clean asm-0
	${CCMD} -c tests/test_0.c 
	${CCMD} ${OBJ} -o test_0.run
	${RUN}

test-1: clean asm-1
	${CCMD} -c tests/test_1.c 
	${CCMD} ${OBJ} -o test_1.run
	${RUN}

test-2: clean asm-2
	${CCMD} -Wno-overlength-strings -c tests/test_2.c 
	${CCMD} -Wno-overlength-strings ${OBJ} -o test_2.run
	${RUN}

test-3: clean asm-3
	${CCMD} -c tests/test_3.c 
	${CCMD} ${OBJ} -o test_3.run
	${RUN}

test-4: clean asm-4
	${CCMD} -c tests/test_4.c 
	${CCMD} ${OBJ} -o test_4.run
	${RUN}

test-5: clean asm-5
	${CCMD} -c tests/test_5.c 
	${CCMD} ${OBJ} -o test_5.run
	${RUN}

test-6: clean asm-6
	${CCMD} -c tests/test_6.c 
	${CCMD} ${OBJ} -o test_6.run
	${RUN}

test-7: clean asm-7 asm-0
	${CCMD} -c tests/test_7.c 
	${CCMD} ${OBJ} -o test_7.run
	${RUN}

test-8: clean asm-8
	${CCMD} -c tests/test_8.c 
	${CCMD} ${OBJ} -o test_8.run
	${RUN}

test-9: clean asm-9
	${CCMD} -c tests/test_9.c 
	${CCMD} ${OBJ} -o test_9.run
	${RUN}

test-10: clean asm-10
	${CCMD} -c tests/test_10.c 
	${CCMD} ${OBJ} -o test_10.run
	${RUN}

######## ASM TASKS

asm-0:
	${ASD} 0-strlen.asm

asm-1:
	${ASD} 1-strcmp.asm

asm-2:
	${ASD} 2-strncmp.asm

asm-3:
	${ASD} 3-strchr.asm

asm-4:
	${ASD} 4-strstr.asm

asm-5:
	${ASD} 5-memcpy.asm

asm-6:
	${ASD} 6-putc.asm

asm-7:
	${ASD} 7-puts.asm

asm-8:
	${ASD} 8-strcasecmp.asm

asm-9:
	${ASD} 9-strncasecmp.asm

asm-10:
	${ASD} 10-strspn.asm

######## UTILITY

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
