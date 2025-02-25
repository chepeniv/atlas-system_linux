CC = gcc
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
DEFS = $(shell find defs/*.c)
CFLAGS = -Wall -Werror -Wextra -ggdb3
DB_FLAGS = -ggdb3
CCMD = ${CC} ${I_FLAGS} ${CFLAGS} ${L_FLAGS} ${DB_FLAGS}

# I_FLAGS = $(shell pkg-config --cflags gtk4)
# L_FLAGS = $(shell pkg-config --libs gtk4)

.DELETE_ON_ERROR:

.PHONY: clean defs

all: 0-hreadelf 1-hreadelf 2-hreadelf

0-hreadelf: defs
	${CC} ${CFLAGS} *.o 0-hreadelf.c -o 0-hreadelf

1-hreadelf: defs
	${CC} ${CFLAGS} *.o 1-hreadelf.c -o 1-hreadelf

2-hreadelf: defs
	${CC} ${CFLAGS} *.o 2-hreadelf.c -o 2-hreadelf

defs:
	${CC} ${CFLAGS} -c ${DEFS}

clean:
	$(RM) -v *~ *.exec *.o *.out *.x  *-hreadelf defs/*.o
