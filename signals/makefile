CC = gcc
GDB = cgdb
MEMTEST = valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all
CFLAGS = -Wall -Werror -Wextra -pedantic 
DB_FLAGS = -ggdb3
CCMD = ${CC} ${CFLAGS} ${DB_FLAGS}
OBJ = *.o
RUN = ./run-*

.DELETE_ON_ERROR:

.PHONY: clean

######## GLOBAL

all: 

clean:
	$(RM) -v *~ *.exec *.o *.out *.x run_* *.run *.start
